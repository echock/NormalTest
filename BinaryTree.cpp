#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<stack>
#include<queue>
using namespace std;

template<class Type>
class BinaryTree
{
protected:
	struct BtNode
	{
		Type data;
		BtNode *leftchild;
		BtNode *rightchild;
	};
private:
	BtNode *root;
	Type RefValue;

	static BtNode * _Buynode()
	{
		BtNode *s = (BtNode *)malloc(sizeof(BtNode));
		if(s == NULL) exit(1);
		memset(s,0,sizeof(BtNode));
		return s;
	}
	static void PreOrder(BtNode *p)
	{
		if(p != NULL)
		{
			cout<<p->data<<"  ";
			PreOrder(p->leftchild);
			PreOrder(p->rightchild);
		}
	}
	static void InOrder(BtNode *p)
	{
		if(p != NULL)
		{
			InOrder(p->leftchild);
			cout<<p->data<<"  ";
			InOrder(p->rightchild);
		}
	}
	static void PastOrder(BtNode *p)
	{
		if(p != NULL)
		{
			PastOrder(p->leftchild);
			PastOrder(p->rightchild);
			cout<<p->data<<"  ";
		}
	}
	BtNode * Create(const Type *&str)
	{
		BtNode *s = NULL;
		if(*str != RefValue)
		{
			s = _Buynode();
			s->data = *str;
			// new (&s->data) Type(*str);
			s->leftchild = Create(++str);
			s->rightchild = Create(++str);
		}
		return s;
	}
	static void Clear(BtNode *p)
	{
		if(p != NULL)
		{
			Clear(p->leftchild);
			Clear(p->rightchild);
			free(p);
		}
	}
	static BtNode * Find(BtNode *ptr,const Type &x)
	{
		if(ptr == NULL || ptr->data == x) return ptr;
		else
		{
			BtNode *p = Find(ptr->leftchild,x);
			if(NULL == p)
			{
				p = Find(ptr->rightchild,x);
			}
			return p;
		}
	}
	static BtNode * Parent(BtNode *ptr,const BtNode *child)
	{
		if(ptr == NULL || ptr->leftchild == child 
			|| ptr->rightchild == child)
		{
			return ptr;
		}
		else
		{
			BtNode * p = Parent(ptr->leftchild,child);
			if(NULL == p)
			{
				p = Parent(ptr->rightchild,child);
			}
			return p;
		}
	}
	BtNode * Copy(BtNode *ptr)
	{
		BtNode *s = NULL;
		if(ptr != NULL)
		{
			s=_Buynode();
			s->data = ptr->data;
			s->leftchild =Copy(ptr->leftchild);
			s->rightchild = Copy(ptr->rightchild);
		}
		return s;
	}
	static bool equal(BtNode *pa,BtNode *pb)
	{
		return ((pa == NULL && pb == NULL) || (pa != NULL 
			&& pb != NULL && pa->data == pb->data 
			&& equal(pa->leftchild,pb->leftchild)
			&& equal(pa->rightchild,pb->rightchild)));
	}
public:
	typedef BtNode * PBtNode;
	const Type & GetRefValue() const { return RefValue;}
	BtNode * GetRoot() const { return root;}
	BinaryTree(const Type &x):root(NULL),RefValue(x) {}
	BinaryTree(const BinaryTree<Type> &bt)
		:RefValue(bt.RefValue)
	{
		root = Copy(bt.root);
	}
	BinaryTree<Type> & operator=(const BinaryTree<Type> &bt)
	{
		if(this != &bt)
		{
			this->Clear();
			RefValue = bt.RefValue;
			root =Copy(bt.root);
		}
		return *this;
	}

	~BinaryTree() 
	{
		Clear();
	}
	void Clear()
	{
		Clear(root);
		root = NULL;
	}
	void CreateTree(Type *str)
	{
		if(str != NULL)
		{
			root = Create(str);
		}
	}
	void PreOrder() const
	{
		PreOrder(root);
		cout<<endl;
	}
	void InOrder() const
	{
		InOrder(root);
		cout<<endl;
	}
	void PastOrder() const
	{
		PastOrder(root);
		cout<<endl;
	}

	BtNode * FindValue(const Type &x) const
	{
		if(x == RefValue) return NULL;
		else Find(root,x);
	}

	BtNode * FindParent(const BtNode * child) const
	{
		if(root == NULL || child == NULL || root == child)
			return NULL;
		else Parent(root,child);
	}

	bool operator==(const BinaryTree<Type> &bt) const
	{
		return equal(this->root,bt.root);
	}
	bool operator!=(const BinaryTree<Type> &bt) const
	{
		return !(*this == bt);
	}
};
////////////////////////////

template<class Type>
class TreeIterator
{
protected:
	BinaryTree<Type> &tree;
	BinaryTree<Type>::PBtNode _Ptr;
public:
	TreeIterator(BinaryTree<Type> &bt):tree(bt),_Ptr(NULL){}
	virtual ~TreeIterator() {}

	Type & operator*() { return _Ptr->data;}
	const Type &operator*() const { return _Ptr->data;}
	bool IsDone() const { return _Ptr == NULL;}

	virtual void First() = 0;
	virtual void operator++() = 0;
};
///////////////////////////////////////////
template<class Type>
struct StkNode
{
	BinaryTree<Type>::PBtNode pnode;
	int                       popnum;
public:
	StkNode(BinaryTree<Type>::PBtNode p=NULL):pnode(p),popnum(0)
	{}
};

template<class Type>
class PastIterator : public TreeIterator<Type>
{
protected:
	stack<StkNode<Type> > st;
public:
	PastIterator(BinaryTree<Type> &bt):TreeIterator<Type>(bt){}
	~PastIterator() {}
	void First()
	{
		_Ptr = NULL;
		if(tree.GetRoot() != NULL)
		{
			st.push(StkNode<Type>(tree.GetRoot()));
			operator++();
		}
	}
	void operator++()
	{
		if(st.empty())
		{
			_Ptr = NULL;
			return ;
		}
		StkNode<Type> node;
		for(;;)
		{
			node = st.top();
			st.pop();
			if(++node.popnum == 3)
			{
				_Ptr = node.pnode;
				return;
			}
			st.push(node);
			if(node.popnum == 1 && node.pnode->leftchild != NULL)
			{
				st.push(StkNode<Type>(node.pnode->leftchild));
			}if(node.popnum == 2 && node.pnode->rightchild != NULL)
			{
				st.push(StkNode<Type>(node.pnode->rightchild));
			}
		}
	}
};

template<class Type>
class InIterator :public PastIterator<Type>
{
public:
	InIterator(BinaryTree<Type> &bt):PastIterator<Type>(bt)
	{}
	~InIterator() {}
//	void First()// this
//	{
//		_Ptr = NULL;
//		if(tree.GetRoot() != NULL)
//		{
//			st.push(StkNode<Type>(tree.GetRoot()));
//			operator++();
//		}
//	}
	void operator++()
	{
		
		if(st.empty())
		{
			_Ptr = NULL;
			return ;
		}
		StkNode<Type> node;
		for(;;)
		{
			node = st.top();
			st.pop();
			if(++node.popnum == 2)
			{
				_Ptr = node.pnode;
				if(node.pnode->rightchild != NULL)
				{
					st.push(StkNode<Type>(node.pnode->rightchild));
				}
				return;
			}
			st.push(node);
			if(node.popnum == 1 && node.pnode->leftchild != NULL)
			{
				st.push(StkNode<Type>(node.pnode->leftchild));
			}
		}
	}
};

template<class Type>
class PreIterator: public TreeIterator<Type>
{
protected:
	stack<BinaryTree<Type>::PBtNode> st;
public:
	PreIterator(BinaryTree<Type> &bt):TreeIterator<Type>(bt) {}
	~PreIterator() {}
	void First()
	{
		_Ptr = NULL;
		if(tree.GetRoot() != NULL)
		{
			st.push(tree.GetRoot());
			operator++();
		}

	}
	void operator++()
	{
		if(st.empty())
		{
			_Ptr = NULL;
			return ;
		}
		_Ptr = st.top(); st.pop();
		if(_Ptr->rightchild != NULL)
		{
			st.push(_Ptr->rightchild);
		}
		if(_Ptr->leftchild != NULL)
		{
			st.push(_Ptr->leftchild);
		}
	}
};


template<class Type>
class LevelIterator : public TreeIterator<Type>
{
protected:
	queue<BinaryTree<Type>::PBtNode > qu;
public:
	LevelIterator(BinaryTree<Type> &bt):TreeIterator<Type>(bt) {}
	~LevelIterator() {}
	void First()// qu.push; qu.front(); qu.pop();
	{
		_Ptr = NULL;
		if(tree.GetRoot() != NULL)
		{
			qu.push(tree.GetRoot());
			operator++();
		}
	}
	void operator++()
	{
		if(qu.empty())
		{
			_Ptr = NULL;
			return ;
		}
		_Ptr = qu.front(); qu.pop();
		if(_Ptr->leftchild != NULL)
		{
			qu.push(_Ptr->leftchild);
		}
		if(_Ptr->rightchild != NULL)
		{
			qu.push(_Ptr->rightchild);
		}

	}
};
void main()
{
	BinaryTree<char> myt('#');
	char * sp = "ABC##DE##F##G#H##";
	myt.CreateTree(sp);
	PastIterator<char> pi(myt);
	pi.First();
	while(!pi.IsDone())
	{
		cout<<*pi<<" ";
		++pi;
	}
	cout<<endl;
	InIterator<char> ii(myt);
	ii.First();
	while(!ii.IsDone())
	{
		cout<<*ii<<" ";
		++ii;
	}
	cout<<endl;
	PreIterator<char> it(myt);
	it.First();
	while(!it.IsDone())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
	LevelIterator<char> lv(myt);
	lv.First();
	while(!lv.IsDone())
	{
		cout<<*lv<<" ";
		++lv;
	}
	cout<<endl;
}
