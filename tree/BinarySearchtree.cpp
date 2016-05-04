#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<stack>
#include<queue>
using namespace std;
class BSTree
{
protected:
	struct BstNode
	{
		Type key;
		BstNode *parent; //
		BstNode *leftchild;
		BstNode *rightchild;
	};
	static BstNode *_Buynode()
	{
		BstNode * s = (BstNode*)malloc(sizeof(BstNode));
		if(s == NULL) exit(1);
		memset(s,0,sizeof(BstNode));
		return s;
	}
	static void _Freenode(BstNode *p)
	{
		free(p);
	}
	static BstNode *FindValue(BstNode *ptr,Type kx)
	{
		
		while(ptr!=NULL&&ptr->key!=kx)
		{
			ptr = ptr->key>kx?ptr->leftchild:ptr->rightchild;

		}
		return ptr;
	}
	static BstNode *SearchValue(BstNode *ptr,Type kx)
	{
		if(ptr==NULL||ptr->key==kx)
			return ptr;
		if(ptr->key>kx)
			return SearchValue(ptr->rightchild,kx);
		else
			return SearchValue(ptr->leftchild,kx);
	}
	static BstNode *First(BstNode*ptr)
	{
		while(ptr!=NULL&&ptr->leftchild!=NULL)
			ptr = ptr->leftchild;]
		return ptr;
	}
	static BstNode*Last(BstNode *ptr)
	{
		while(ptr!=NULL&&ptr->rightchild!=NULL)
			ptr = ptr->rightchild;
		return ptr;
	}
	static BstNode*Next(BstNode *ptr)
	{
		if(ptr==NULL)
			return NULL;
		if(ptr->rightchild!=NULL)
			return First(ptr->rightchild);
		else
		{
			BstNode *pa = ptr->parent;
			while(pa!=NULL&&ptr==pa->rightchild)
			{
				ptr = pa;
				pa = pa->parent;
			}
			return pa;
		}
	}
	static BstNode *Prev(BstNode *ptr)
	{
		if(ptr==NULL)
			return ptr;
		if(ptr->leftchild!=NULL)
			return Last(ptr->leftchild);
		else
		{
			BstNode *pa = ptr->parent;
			while(pa!=NULL&&ptr->leftchild==pa)
			{
				ptr = pa;
				pa = pa->parent;
			}
			return pa;
		}
	}
	static bool Insert(BstNode *&ptr,const Type&x,BstNode *pa)
	{
		bool res = false;
		if(ptr==NULL)
		{
			ptr = _Buynode();
			ptr->key = x;
			ptr->parent = pa;
			res = true;
		}
		else if(x<ptr->key)
		{
			res = Insert(ptr->leftchild,x,ptr);
		}
		else if(x<ptr->key)
		{
			res = Insert(ptr->rightchild,x,ptr);
		}
		return res;
	}
	private:
		BstNode *root;
		Type RefValue;
	public:
	BSTree(const Type &x):root(NULL),RefValue(x) {}
	~BSTree() {}
	const Type & GetRefValue() const { return RefValue;}
	bool Insert(const Type &x)
	{
		bool res = false;
		if(x!=RefValue)
		{
			res = Insert(root,x,NULL);
		}
		return res;
	}
	static bool Remove(BstNode *&ptr,const Type&x)
	{
		bool res = false;
		if(ptr==NULL)
			return res;
		if(x<ptr->key)
			res = Remove(ptr->leftchild,x);
		else if(x>ptr->key)
			res = Remove(ptr->rightchild,x);
		else if(ptr->leftchild!=NULL&&ptr->rightchild!=NULL)
		{
			BstNode *q = Next(ptr);
			ptr->key = q->key;
			res = Remove(q,q->key);
		}
		else
		{
			BstNode *child = ptr->leftchild !=  NULL? ptr->leftchild:ptr->rightchild;
			if(child != NULL) child->parent = ptr->parent;
			BstNode *q = ptr;
			ptr = child;
			_Freenode(q);
			res = true;	
		}
		return res;
	}
	bool Remove(const Type &x)
	{
		bool res  = false;
		if(x != RefValue)
		{
			res = Remove(root,x);
		}
		return res;
	}
	void InOrder() const
	{
		for(BstNode *p = First(root); p != NULL; p = Next(p))
		{
			cout<<p->key<<" ";
		}
		cout<<endl;
	}


};
void main()
{
	BSTree<int> myt(-1);
	int ar[]={53,17,78,9,45,65,87,23,81,94,88,23,100,17,110};
	int n = sizeof(ar)/sizeof(ar[0]);
	for(int i = 0;i<n; ++i)
	{
		cout<<myt.Insert(ar[i])<<" : ";
		myt.InOrder();
	}
	int kx;
	while(cin>>kx, kx != myt.GetRefValue())
	{
		cout<<myt.Remove(kx)<<" : ";
		myt.InOrder();
	}
}