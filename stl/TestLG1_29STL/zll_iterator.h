
#ifndef ZLL_ITERATOR
#define ZLL_ITERATOR
#include<typeinfo>
//#include<iostream>
using namespace std;

namespace zll
{

	typedef int ptrdiff_t;

			// ITERATOR TAGS (from <iterator>)
struct input_iterator_tag {};
struct output_iterator_tag {};

struct forward_iterator_tag: public input_iterator_tag {};

struct bidirectional_iterator_tag: 	public forward_iterator_tag {};

struct random_access_iterator_tag: 	public bidirectional_iterator_tag  {};

//////////////////////////////////////////////
template<class Category,class T,class Distance = ptrdiff_t,
         class Pointer = T*, class Reference = T&>
 struct iterator
 {
	 typedef Category  iterator_category;
	 typedef T         value_type;
	 typedef Distance  difference_type;
	 typedef Pointer   pointer;
	 typedef Reference reference;
 };

template<class _Ty,class _Dist>
struct _Bidit : public iterator<bidirectional_iterator_tag,
	                _Ty,_Dist,_Ty*,_Ty&>
{
};

template<class _Ty,class _Dist>
struct _Ranit: public iterator<random_access_iterator_tag,
	                 _Ty,_Dist,_Ty*,_Ty&>
{
};

 template<class _It>// _It ==> iterator;
 struct iterator_traits
 {
	 typedef typename _It::iterator_category iterator_category;
	 typedef typename _It::value_type        value_type;
	 typedef typename _It::difference_type   difference_type;
	 typedef typename _It::pointer           pointer;
	 typedef typename _It::reference         reference;
 };
 //////////////////////////////////
 // SGI
template<class T>
struct iterator_traits<T*>
{
	typedef random_access_iterator_tag iterator_category;
	typedef T   value_type;
	typedef int difference_type;
	typedef T * pointer;
	typedef T&  reference;
};
template<class T>
struct iterator_traits<const T*>
{
	typedef random_access_iterator_tag iterator_category;
	typedef T     value_type;
	typedef int   difference_type;
	typedef const T * pointer;
	typedef const T&  reference;
};
/////////////////////////////////////////
template<class _II>
typename iterator_traits<_II>::iterator_category
iterator_category(const _II &)
{
	typedef typename iterator_traits<_II>::iterator_category category;
	return category();
}
template<class _II>
typename iterator_traits<_II>::value_type *
value_type(const _II &)
{
	typedef typename iterator_traits<_II>::value_type value_type;
	return static_cast<value_type*>(0);
}

template<class _II>
typename iterator_traits<_II>::difference_type *
difference_type(const _II &)
{
	typedef typename iterator_traits<_II>::difference_type difference_type;
	return static_cast<difference_type*>(0);
}
//////////////////////////////////////
//vc
template<class Category,class T,class Distance,
         class Pointer, class Reference>
Category _Iter_Cat(const iterator<Category,T,Distance,Pointer,Reference> &)
{
	return Category();
}

template<class T>
random_access_iterator_tag _Iter_Cat(const T *)
{
	return random_access_iterator_tag();
}

//////////////////////////////////////
template<class _II,class Dist>
inline void __advance(_II &i,Dist n,input_iterator_tag )
{
	while(n--) ++i;
}

template<class _FI,class Dist>
inline void __advance(_FI &i,Dist n,forward_iterator_tag)
{
	__advance(i,n,input_iterator_tag());
}
template<class _BI,class Dist>
inline void __advance(_BI &i,Dist n,bidirectional_iterator_tag )
{
	if(n>= 0)
	{
		while(n--) ++i;
	}else
	{
		while(n++) --i;
	}
}

template<class _RAI,class Dist>
inline void __advance(_RAI &i,Dist n,random_access_iterator_tag)
{
	i+=n;
}

template<class _II,class Dist>
inline void advance(_II &i,Dist n)
{
	//const char *ii={typeid(_II).name()};
	//const char *it={typeid(iterator_traits<_II>::iterator_category).name()};

	//typedef typename iterator_traits<_II>::iterator_category category;
	//__advance(i,n,category());
	//__advance(i,n,iterator_category(i));
	__advance(i,n,_Iter_Cat(i));

}
//////////////////////////////////////

template<class _II>
typename iterator_traits<_II>::difference_type
__distance(_II _F, _II _L,input_iterator_tag)
{
	typename iterator_traits<_II>::difference_type n = 0;
	while(_F != _L)
	{
		++n;
		++_F;
	}
	return n;
}
template<class _RAI>
typename iterator_traits<_RAI>::difference_type
__distance(_RAI _F, _RAI _L,random_access_iterator_tag)
{
	return _L - _F;
}

template<class _II>
typename iterator_traits<_II>::difference_type
distance(_II _F, _II _L)
{
	return __distance(_F,_L,iterator_category(_F));
}

};

#endif