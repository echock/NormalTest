
#include"zll_list.h"


class Shape
{
	int x,y;
	int r;
public:
	Shape():x(0),y(0),r(0) {}
	Shape(const Shape &s):x(s.x),y(s.y),r(s.r) {}
	~Shape()
	{
	}
};

namespace zll
{
template<>
struct __type_traits<Shape>
{
	
	typedef __true_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_operator;
	typedef __true_type has_trivial_destructor;
	typedef __true_type is_POD_type; // int c struct;
};

};



void main()
{
	Shape s;
	zll::List<Shape> slist;
	for(int i = 0;i<100;++i)
	{
		slist.push_back(s);
	}
	slist.clear();
}



