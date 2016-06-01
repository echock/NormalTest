
#ifndef ZLL_ALLOC
#define ZLL_ALLOC


namespace zll
{
#include<malloc.h>

#if 0
#include<new>
#define __THROW_BAD_ALLOC throw std::bad_alloc();
#elif !defined(__THROW_BAD_ALLOC)
//#include<iostream>
#include<stdlib.h>
#define __THROW_BAD_ALLOC exit(1); //std::cerr<<"out of memory"<<std::endl; exit(1);
#endif

template<int ints>
class __malloc_alloc_template
{
private:
	//以下函数用来处理内存不足的情况
	static void * oom_malloc(size_t n)
	{
		void (*my_malloc_handler)() = NULL;
		void *result = NULL;
		for(;;)
		{
			my_malloc_handler = __malloc_alloc_oom_handler;
			if(NULL == my_malloc_handler)
			{
				__THROW_BAD_ALLOC;
			}
			(*my_malloc_handler)();
			result = malloc(n);
			if(NULL != result)
			{
				return result;
			}
		}
	}
	static void * oom_realloc(void *p,size_t n)
	{
		void (*my_malloc_handler)() = NULL;
		void *result = NULL;
		for(;;)
		{
			my_malloc_handler = __malloc_alloc_oom_handler;
			if(NULL == my_malloc_handler)
			{
				__THROW_BAD_ALLOC;
			}
			(*my_malloc_handler)();
			result = realloc(p,n);
			if(NULL != result)
			{
				return result;
			}
		}
	}
	static void (*__malloc_alloc_oom_handler)();
public:

	static void * allocate(size_t n)
	{
		void *result = malloc(n);//第一级配置器直接使用malloc
		if(NULL == result)
		{
			result = oom_malloc(n);
		}
		return result;
	}
	static void deallocate(void *p,size_t)
	{
		free(p);
	}
	static void * reallocate(void *p,size_t old_sz,size_t new_sz)
	{
		void *result = realloc(p,new_sz);
		if(NULL == result)
		{
			result = oom_realloc(p,new_sz);
		}
		return result;
	}
	// new.h set_new_handler
	static void(*set_malloc_handler(void (*f)()))()
	{
		void (*old)() = __malloc_alloc_oom_handler;
		__malloc_alloc_oom_handler = f;
		return old;
	}
};

template<int ints>
void (* __malloc_alloc_template<ints>::__malloc_alloc_oom_handler)() = NULL;

typedef __malloc_alloc_template<0> malloc_alloc;
//////////////////////////////////////////////////////

enum { __ALIGN = 8 };
enum { __MAX_BYTES = 128};
enum { __NFREELISTS = __MAX_BYTES/__ALIGN}; // 16

template<bool threads,int ints>
class __default_alloc_template
{
private:
	//将bytes上调至8的倍数
	static size_t ROUND_UP(size_t bytes)
	{
		return (bytes + __ALIGN - 1) & ~(__ALIGN - 1);
	}
private:
	//free-list的节点构造
	union obj
	{
		union obj *free_list_link;
		char client_data[1];/////
	};
private:
	//16个自由链表
	static obj * volatile free_list[__NFREELISTS];
	//以下函数根据区块大小，决定使用第n号自由链表，n从0计算
	static size_t FREELIST_INDEX(size_t bytes)
	{
		return ((bytes + __ALIGN - 1) / __ALIGN) -1;
	}
private:
	static char * start_free;
	static char * end_free;
	static size_t heap_size;

	//从内存池中取空间给自由链表用
	static char * chunk_alloc(size_t size,int &nobjs)
	{
		char * result = NULL;
		size_t total_bytes = size*nobjs;
		size_t bytes_left = end_free - start_free;//内存池剩余空间
		if(bytes_left >= total_bytes)
		{
			//内存池剩余空间完全满足需求量
			result = start_free;
			start_free += total_bytes;
			return result;
		}else if(bytes_left >= size)
		{//内存池剩余空间不能完全满足需求量，但足够供应一个（含）以上的区块
			nobjs = bytes_left/size;
			total_bytes = size*nobjs;
			result = start_free;
			start_free += total_bytes;
			return result;
		}else
		{ 
			//内存池剩余空间连一个区块的大小都无法提供
			size_t bytes_to_get = 2*total_bytes + ROUND_UP(heap_size>>4);
			//以下试着让内存池中的残余零头还有利用价值
			if(bytes_left> 0)
			{
				/*
				内存池中还有一些零头，先配个适当的free-list
				首先寻找适当的free-list
				*/
				obj * volatile * my_free_list = free_list + FREELIST_INDEX(bytes_left);
				//调整free-list，将内存池中的残余空间编入
				((obj*)start_free)->free_list_link = *my_free_list;
				*my_free_list = ((obj*)start_free);
			}
			//配置heap空间，用来补充内存池
			start_free = end_free = NULL;
			start_free = (char*)malloc(bytes_to_get);
			if(NULL == start_free)
			{
				int i;
				obj * volatile * my_free_list= NULL, *p=NULL;
				for(i = size; i<= __MAX_BYTES; i+=__ALIGN)
				{
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;
					if(NULL != p)
					{
						*my_free_list = p->free_list_link;
						start_free = (char*)p;
						end_free = start_free + i;
						return chunk_alloc(size,nobjs);
					}
				}
				start_free =(char*) malloc_alloc::allocate(bytes_to_get);
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return chunk_alloc(size,nobjs);
		}
	}
	static void *refill(size_t n)// n = 16 * nobjs = 320
	{
		int nobjs = 20;
		char *chunk =  chunk_alloc(n,nobjs);
		if(nobjs == 1) return chunk;
		obj *result = (obj*)chunk;
		obj * volatile * my_free_list = free_list + FREELIST_INDEX(n);
		obj * current_obj = NULL,*next_obj= NULL;
		*my_free_list = next_obj =(obj*)((chunk)+n);
		for(int i = 1; ; ++i)
		{
			current_obj = next_obj;
			next_obj = (obj*)((char*)next_obj + n);
			if(nobjs - 1 == i)
			{
				current_obj->free_list_link = NULL;
				break;
			}else
			{
				current_obj->free_list_link = next_obj;
			}
		}
		return result;
	}
public:
	static void *allocate(size_t n)
	{
		obj * volatile * my_free_list = NULL;
		obj *result = NULL; 
		if(n > (size_t) __MAX_BYTES)
		{
			return malloc_alloc::allocate(n);
		}
		my_free_list = free_list + FREELIST_INDEX(n);
		result = *my_free_list;
		if(result == NULL)
		{
			return refill(ROUND_UP(n));
		}
		*my_free_list = result->free_list_link;
		return result;

	}
	static void deallocate(void *p,size_t n)
	{
		obj * volatile * my_free_list = NULL;
		obj *q = (obj*)p; 
		if(n > (size_t) __MAX_BYTES)
		{
			malloc_alloc::deallocate(p,n);
			return ;
		}
		my_free_list = free_list + FREELIST_INDEX(n);
		q->free_list_link = *my_free_list;
		*my_free_list = q;

	}
	static void *reallocate(void *p,size_t old_sz,size_t new_sz);
};

template<bool threads,int ints>
typename __default_alloc_template<threads,ints>::obj * volatile 
__default_alloc_template<threads,ints>::free_list[__NFREELISTS];

template<bool threads,int ints>
char * __default_alloc_template<threads,ints>::start_free= NULL;

template<bool threads,int ints>
char * __default_alloc_template<threads,ints>::end_free= NULL;

template<bool threads,int ints>
size_t __default_alloc_template<threads,ints>::heap_size = 0;


#ifdef __USE_MALLOC
typedef __malloc_alloc_template<0> malloc_alloc;
typedef malloc_alloc alloc;
#else
typedef __default_alloc_template<false,0> alloc;
#endif

template<class T, class Alloc>
class simple_alloc
{
public:
	static T * allocate(size_t n)
	{
		return 0 == n? NULL:(T*)Alloc::allocate(n*sizeof(T));
	}
	static T * allocate()
	{
		return (T*)Alloc::allocate(sizeof(T));
	}
	static void deallocate(T *p,size_t n)
	{
		if(0 != n)
		{
			Alloc::deallocate(p,n*sizeof(T));
		}
	}
	static void deallocate(T *p)
	{
		Alloc::deallocate(p,sizeof(T));
	}
};





/*typedef unsigned int size_t;
typedef int          ptrdiff_t;

#define _PDFT	ptrdiff_t 
#define _SIZT	size_t

#define _POINTER_X(T, A)	T  *
#define _REFERENCE_X(T, A)	T  &

template<class _Ty> inline
_Ty  *_Allocate(_PDFT _N, _Ty  *)
{
	if (_N < 0)
		_N = 0;
	return ((_Ty *)operator new((_SIZT)_N * sizeof (_Ty))); 
}

template<class _T1, class _T2> inline
void _Construct(_T1  *_P, const _T2& _V)
{
	new ((void *)_P) _T1(_V); 
}

template<class _Ty> inline
void _Destroy(_Ty  *_P)
{
	//_DESTRUCTOR(_Ty, _P); 
	_P->~_Ty();
}

inline void _Destroy(char  *_P)
{}
inline void _Destroy(wchar_t  *_P)
{}

template<class _Ty>
class allocator 
{
public:
	typedef _SIZT size_type;
	typedef _PDFT difference_type;

	typedef _Ty  *pointer;
	typedef const _Ty  *const_pointer;
	typedef _Ty & reference;
	typedef const _Ty & const_reference;
	typedef _Ty value_type;


	pointer address(reference _X) const
	{
		return (&_X); 
	}
	const_pointer address(const_reference _X) const
	{
		return (&_X);
	}
	pointer allocate(size_type _N, const void *)
	{
		return (_Allocate((difference_type)_N, (pointer)0));
	}
	char  *_Charalloc(size_type _N)
	{
		return (_Allocate((difference_type)_N,(char *)0)); 
	}
	void deallocate(void  *_P, size_type)
	{
		operator delete(_P); 
	}
	void construct(pointer _P, const _Ty& _V)
	{
		_Construct(_P, _V); 
	}
	void destroy(pointer _P)
	{
		_Destroy(_P); 
	}
	_SIZT max_size() const
	{
		_SIZT _N = (_SIZT)(-1) / sizeof (_Ty);
		return (0 < _N ? _N : 1); 
	}
};
template<class _Ty, class _U> inline
bool operator==(const allocator<_Ty>&, const allocator<_U>&)
{
	return (true); 
}
template<class _Ty, class _U> inline
bool operator!=(const allocator<_Ty>&, const allocator<_U>&)
{
	return (false); 
}


template<> 
class allocator<void> 
{
public:
	typedef void _Ty;
	typedef _Ty *pointer;
	typedef const _Ty  *const_pointer;
	typedef _Ty value_type;
};

*/

};

#endif
