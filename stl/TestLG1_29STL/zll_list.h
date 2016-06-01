

#ifndef ZLL_LIST
#define ZLL_LIST
#include"zll_construct.h"
#include"zll_alloc.h"
#include"zll_iterator.h"
namespace zll
{

template<class _Ty,class Alloc = alloc>
class List
{
public:
	typedef List<_Ty>   _Myt;

	typedef _Ty         value_type;
	typedef _Ty  *      _Tptr;
	typedef const _Ty * _Ctptr;
	typedef _Ty &       reference;
	typedef const _Ty & const_reference;
	
	typedef int         difference_type;
	typedef size_t      size_type;
protected:
	struct _Node;
	typedef struct _Node * _Nodeptr;
	struct _Node
	{
		_Nodeptr _Prev,_Next;
		_Ty      _Value;
	};
	typedef simple_alloc<_Node,Alloc> data_allocate;
	struct _Acc;
	struct _Acc
	{
		typedef _Ty &    _Vref;
		typedef _Node *& _Nodepref;

		static _Vref _Value(_Nodeptr _P)
		{
			return (*_P)._Value;
		}
		static _Nodepref _Prev(_Nodeptr _P)
		{
			return (*_P)._Prev;
		}
		static _Nodepref _Next(_Nodeptr _P)
		{
			return (*_P)._Next;
		}
	};
public:
	class const_iterator; // const int *p;
	class iterator;       // int *p;
	friend class const_iterator;
	class const_iterator : public _Bidit<_Ty,int>
	{
	public:
		const_iterator() {}
		const_iterator(_Nodeptr _P):_Ptr(_P) {}
		const_reference operator*() const
		{
			return _Acc::_Value(_Ptr);
		}
		_Ctptr operator->() const
		{
			return &**this;
		}
		const_iterator & operator++()
		{
			_Ptr = _Acc::_Next(_Ptr);
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator _tmp = *this;
			++*this;
			return _tmp;
		}

		const_iterator & operator--()
		{
			_Ptr = _Acc::_Prev(_Ptr);
			return *this;
		}
		const_iterator operator--(int)
		{
			const_iterator _tmp = *this;
			--*this;
			return _tmp;
		}

		bool operator==(const const_iterator &_X) const
		{
			return _Ptr == _X._Ptr;
		}
		bool operator!=(const const_iterator &_X) const
		{
			return !(*this == _X);
		}
		_Nodeptr _Mynode() const
		{
			return _Ptr;
		}
	protected:
		_Nodeptr _Ptr;
	};

	friend class iterator;
	class iterator : public const_iterator
	{
	public:
		iterator() {}
		iterator(_Nodeptr _P):const_iterator(_P) {}
		reference operator*() const
		{
			return _Acc::_Value(_Ptr);
		}
		_Tptr operator->() const
		{
			return &**this;
		}
		iterator & operator++()
		{
			_Ptr = _Acc::_Next(_Ptr);
			return *this;
		}
		iterator operator++(int)
		{
			iterator _tmp = *this;
			++*this;
			return _tmp;
		}

		iterator & operator--()
		{
			_Ptr = _Acc::_Prev(_Ptr);
			return *this;
		}
		iterator operator--(int)
		{
			iterator _tmp = *this;
			--*this;
			return _tmp;
		}
		bool operator==(const iterator &_X) const
		{
			return _Ptr == _X._Ptr;
		}
		bool operator!=(const iterator &_X) const
		{
			return !(*this == _X);
		}
	};
public:
	iterator begin()
	{
		return iterator(_Acc::_Next(_Head));
	}
	const_iterator begin() const
	{
		return const_iterator(_Acc::_Next(_Head));
	}
	iterator end()
	{
		return iterator(_Head);
	}
	const_iterator end() const
	{
		return const_iterator(_Head);
	}
public:
	List():_Head(_Buynode()),_Size(0){}
	typedef const_iterator _It;

	List(size_type _N,const _Ty &_X)
		:_Head(_Buynode()),_Size(0)
	{
		insert(begin(),_N,_X);
	}
	List(const _Ty *_F,const _Ty *_L)
		:_Head(_Buynode()),_Size(0)
	{
		insert(begin(),_F,_L);
	}
	List(_It _F,_It _L):_Head(_Buynode()),_Size(0)
	{
		insert(begin(),_F,_L);
	}
	List(const _Myt &_X)
		:_Head(_Buynode()),_Size(0)
	{
		insert(begin(),_X.begin(),_X.end());
	}
	_Myt & operator=(const _Myt &_X)
	{
		if(this != &_X)
		{
			iterator _F1=begin(),_L1 = end();
			const_iterator _F2 = _X.begin(), _L2 = _X.end();
			for(; _F1 != _L1 && _F2 != _L2; ++_F1,++_F2)
			{
				*_F1 = *_F2;
			}
			erase(_F1,_L1);
			insert(_L1,_F2,_L2);
		}
		return *this;
	}
	~List()
	{
		clear();
		_Freenode(_Head);
		_Head = NULL;
		_Size = 0;
	}
	reference back() { return *--end();}
	const_reference back()const { return *--end();}

	reference front() { return *begin();}
	const_reference front() const{ return *begin();}

	size_type size() const { return _Size;}
	bool empty() const { return size() == 0;}
	void assign(_It _F,_It _L)
	{
		erase(begin(),end());
		insert(begin(),_F,_L);
	}
	void assign(size_type _N,const _Ty &_X = _Ty())
	{
		erase(begin(),end());
		insert(begin(),_N,_X);
	}
	void resize(size_type _N,const _Ty &_X = _Ty())
	{
		if(_N > size())
		{
			insert(end(),_N - size(),_X);
		}else
		{
			while(_N < size())
			{
				pop_back();
			}
		}
	}
	void pop_front()
	{
		erase(begin());
	}
	void pop_back()
	{
		erase(--end());
	}

	void clear()
	{
		//erase(begin(),end());
		zll::destroy(begin(),end());
		iterator _F = begin();
		iterator _L = end();
		for(; _F != _L;)
		{
			_Nodeptr _S = _F++._Mynode();
			_Acc::_Next(_Acc::_Prev(_S)) = _Acc::_Next(_S);
			_Acc::_Prev(_Acc::_Next(_S)) = _Acc::_Prev(_S);
			_Freenode(_S);
		}
		_Size = 0;

	}
	void erase(iterator _F,iterator _L)
	{
		for(; _F != _L;)
		{
			erase(_F++);//????
		}
	}
	void remove(const _Ty &_X)
	{
		iterator _F = begin(), _L = end();
		for(; _F != _L;)
		{
			if(*_F == _X)
			{
				erase(_F++);
			}
			else
			{
				++_F;
			}
		}
	}
	/////
	iterator erase(iterator _P)
	{
		_Nodeptr _S = _P++._Mynode();
		_Acc::_Next(_Acc::_Prev(_S)) = _Acc::_Next(_S);
		_Acc::_Prev(_Acc::_Next(_S)) = _Acc::_Prev(_S);
		//(&_Acc::_Value(_S))->~_Ty();
		destroy(&_Acc::_Value(_S));
		_Freenode(_S);
		_Size-=1;
		return _P;
	}

	void push_back(const _Ty &_X)
	{
		insert(end(),_X);
	}
	void push_front(const _Ty &_X)
	{
		insert(begin(),_X);
	}
	void insert(iterator _P,size_type _N,const _Ty &_X)
	{
		for(; 0 < _N;--_N)
		{
			insert(_P,_X);
		}
	}
	void insert(iterator _P,const _Ty *_F,const _Ty *_L)
	{
		for(; _F != _L; ++_F)
		{
			insert(_P,*_F);
		}
	}
	void insert(iterator _P,_It _F,_It _L)
	{
		for(; _F != _L; ++_F)
		{
			insert(_P,*_F);
		}
	}
	///
	iterator insert(iterator _P,const _Ty &_X)
	{
		_Nodeptr _S = _P._Mynode();
		_Acc::_Prev(_S) = _Buynode(_Acc::_Prev(_S),_S);
		_S = _Acc::_Prev(_S);
		_Acc::_Next(_Acc::_Prev(_S)) = _S;
		//_Acc::_Value(_S) = _X;//??
		//new(&_Acc::_Value(_S)) _Ty(_X);
		construct(&_Acc::_Value(_S),_X);
		_Size+=1;
		return iterator(_S);
	}
private:
	////
	_Nodeptr _Buynode(_Nodeptr _Parg=NULL,_Nodeptr _Narg = NULL)
	{
		//_Nodeptr _S = (_Nodeptr)malloc(sizeof(_Node));
		_Nodeptr _S = data_allocate::allocate();
		if(NULL == _S) exit(1);
		_Acc::_Prev(_S) = _Parg == NULL? _S:_Parg;
		_Acc::_Next(_S) = _Narg == NULL? _S:_Narg;
		return _S;
	}
	void _Freenode(_Nodeptr _P)
	{
		//free(_P);
		data_allocate::deallocate(_P);
	}

	_Nodeptr  _Head;
	size_type _Size;
};

};

#endif
