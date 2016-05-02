#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip>
#include<stack>    // 
#include<queue>
#include<time.h>
using namespace std;
typedef char ElemType;
#define END '#'
typedef struct node
{
	ElemType data;
	struct node *left;
	struct node *right;
}BtNode,*BinaryTree;

BtNode * _Buynode()
{
	BtNode *s = (BtNode*)malloc(sizeof(BtNode));
	if(NULL==s)
		exit(1);
	memset(s,0,sizeof(s));
	return s;
}

void _Freenode(BtNode *s)
{
	free(s);
}
BtNode * CreateTree1()
{
	ElemType x;
	cin>>x;
	BtNode *s = NULL;
	if(x!= END)
	{
		s = _Buynode();
		s->data = x;
		s->left = CreateTree1();
		s->right = CreateTree1();
	}
	return s;
}

void CreateTree2(BtNode *p)
{
	ElemType x;
	cin>>x;
	if(x == END) p = NULL;
	else
	{
		p = _Buynode();
		p->data = x;
		CreateTree2(p->left);
		CreateTree2(p->right);
	}
}

void CreateTree3(BtNode *&p)
{
	ElemType x;
	cin>>x;
	if(x == END) p = NULL;
	else
	{
		p = _Buynode();
		p->data = x;
		CreateTree3(p->left);
		CreateTree3(p->right);
	}
}
void CreateTree4(BtNode ** const p)
{
	ElemType x;
	cin>>x;
	if(x == END) *p = NULL;
	else
	{
		*p = _Buynode();
		(*p)->data = x;
		CreateTree4(&(*p)->left);
		CreateTree4(&(*p)->right);
	}
}
BtNode * CreateTree5(char *&str)
{
	BtNode *s = NULL;
	if(str != NULL && *str != END)
	{
		s = _Buynode();
		s->data = *str;
		s->left = CreateTree5(++str);
		s->right = CreateTree5(++str);
	}
	return s;
}

BtNode * CreateTree6(char ** const str)
{
	BtNode *s = NULL;
	if(str != NULL && *str != NULL && **str != END)
	{
		s = _Buynode();
		s->data = **str;
		s->left = CreateTree6(&++*str);
		s->right = CreateTree6(&++*str);
	}
	return s;
}
struct StkNode
{
	BtNode *pnode;
	int     popnum;
public:
	StkNode(BtNode *p=NULL):pnode(p),popnum(0) {}
};

void NicePastOrder2(BtNode *ptr)
{
	if(ptr == NULL) return ;
	stack<StkNode> st;
	st.push(StkNode(ptr));
	while(!st.empty())
	{
		StkNode node = st.top(); st.pop();
		if(++node.popnum == 3)
		{
			cout<<node.pnode->data<<" ";
		}else
		{
			st.push(node);
			if(node.popnum == 1 && node.pnode->leftchild != NULL)
			{
				st.push(StkNode(node.pnode->leftchild));
			}else if(node.popnum == 2 && node.pnode->rightchild != NULL)
			{
				st.push(StkNode(node.pnode->rightchild));
			}
		}
	}
	cout<<endl;
}

void NiceInOrder2(BtNode *ptr)
{
	if(ptr == NULL) return ;
	stack<StkNode> st;
	st.push(StkNode(ptr));
	while(!st.empty())
	{
		StkNode node = st.top(); st.pop();
		if(++node.popnum == 2)
		{
			cout<<node.pnode->data<<" ";
			if(node.pnode->rightchild != NULL)
			{
				st.push(StkNode(node.pnode->rightchild));
			}
		}else
		{
			st.push(node);
			if(node.popnum == 1 && node.pnode->leftchild != NULL)
			{
				st.push(StkNode(node.pnode->leftchild));
			}
		}
	}
	cout<<endl;
}
void PreOrder(BtNode *s)
{
	if(s!=NULL)
	{
		cout<<s->data<<" ";
		PreOrder(s->left);
		PreOrder(s->right);
	}

}
void NicePreOrder(BtNode*s)
{
	if(s==NULL)
		return;
	stack<BtNode*>  st;
	st.push(s);
	
	while(!st.empty())
	{
		s = st.top();
		st.pop();
		cout<<s->data<<" ";
		if(s->right)
			st.push(s->right);
		if(s->left)
			st.push(s->left);
	}
}

void InOrder(BtNode *s)
{
	if(s!=NULL)
	{
		InOrder(s->left);
		cout<<s->data<<" ";
		InOrder(s->right);
	}
	
}
void NiceInOrder(BtNode *ptr)
{
	stack<BtNode*> st;
	
	while(!st.empty()||ptr!=NULL)
	{
		while(ptr!=NULL)
		{
			st.push(ptr);
			ptr = ptr->left;
		}
		ptr = st.top();
		st.pop();
		cout<<ptr->data<<" ";
		ptr = ptr->right;
	}
}

void PastOrder(BtNode *s)
{
	if(s!=NULL)
	{
		PastOrder(s->left);
		PastOrder(s->right);
		cout<<s->data<<" ";
	}
	cout<<endl;
}
void NicePastOrder(BtNode *ptr)
{
	if(ptr == NULL) return ;
	stack<BtNode* > st;
	BtNode *tag = NULL;
	while(!st.empty() || ptr != NULL)
	{
		while(ptr != NULL)
		{
			st.push(ptr);
			ptr = ptr->left;
		}
		ptr = st.top(); st.pop();
		if(ptr->right == NULL || ptr->right== tag)
		{
			cout<<ptr->data<<" ";
			tag = ptr;
			ptr = NULL;
		}else
		{
			st.push(ptr);
			ptr = ptr->right;
		}
	}
	cout<<endl;
}

BtNode *FindValue(BtNode *ptr,ElemType x)
{
	if(ptr==NULL||ptr->data==x)
		return ptr;
	else
	{
		BtNode *p = FindValue(ptr->left,x);
		if(p==NULL)
			p = FindValue(ptr->right,x);
		return p;
	}

}

int Findls(ElemType *is,int n,ElemType x)
{
	for(int i = 0; i<n;++i)
	{
		if(is[i] == x)
			return i;
	}
	return -1;
}
BtNode* CreateTreePI(char *ps,char *is,ElemType n)
{
	BtNode *s = NULL;
	if(ps!=NULL&&is!=NULL&&n>=1)
	{
		int pos = Findls(is,n,ps[0]);
		if(pos==-1)
			exit(1);
		s = _Buynode();
		s->data = ps[0];
		s->left = CreateTreePI(ps+1,is,pos);
		s->right = CreateTreePI(ps+pos+1,is+pos+1,n-pos-1);
	}
	return s;
}
BtNode *Findp(BtNode *ptr,BtNode*root)
{
	if(root==NULL||root->left==ptr||root->right==ptr)
		return root;
	else
	{
		BtNode *p;
		p	= Findp(ptr,root->left);
		if(p==NULL)
			p = Findp(ptr,root->right);
		return p;
	}
}
BtNode *FindParent(BtNode *ptr,BtNode*root)
{
	if(ptr==NULL||root==NULL||ptr==root)
		return NULL;
	else
	return	Findp(ptr,root);
}

//¶þ²æÊ÷Éî¶È
int Depth(BtNode*ptr)
{
	if(ptr==NULL)
		return 0;
	return  Depth(ptr->left)>Depth(ptr->right)?Depth(ptr->left)+1:Depth(ptr->right)+1;
}
int Size(BtNode*p)
{
	if(p==NULL)
		return 0;
	else
		return Size(p->left)+Size(p->right)+1;
}
void PrintKLevel(BtNode*ptr,int k)
{
	if(ptr!=NULL&&k<=0)
	cout<<ptr->data<<" ";
	else if(ptr!=NULL)
	{
		PrintKLevel(ptr->left,k-1);
		PrintKLevel(ptr->right,k-1);
	}
}
void LevelOrder(BtNode *ptr)
{
	int k = Depth(ptr);
	for(int i = 0;i<k;i++)
		PrintKLevel(ptr,i);
}
void NiceLevelOrder(BtNode *ptr)
{
	queue<BtNode*> qu;
	qu.push(ptr);
	while(!qu.empty())
	{
		ptr = qu.front();
		cout<<ptr->data<<" ";
		qu.pop();
		if(ptr->left)
			qu.push(ptr->left);
		if(ptr->right)	
			qu.push(ptr->right);
	}
	
}

void Destroy(BtNode*ptr)
{
	if(ptr!=NULL)
	{
		Destroy(ptr->left);
		Destroy(ptr->right);
		_Freenode(ptr);
	}
}
BtNode* Findvalue(BtNode*ptr,ElemType x)
{
	if(ptr==NULL||ptr->data==x)
		return ptr;
	else
	{
	BtNode *p = Findvalue(ptr->left,x);
	if(p==NULL)
		p=Findvalue(ptr->right,x);
	return p;
	}
}
bool Is_Full_BinaryTree(BtNode *ptr)
{
	if(ptr==NULL)
		return false;
	int k = Depth(ptr);
	if(2^k-1==Size(ptr))
		return true;

}

void main()
{
	BinaryTree root = NULL;
	
	char *ps = "ABCDEFGH";
	char *is = "CBEDFAGH";
	char *ls = "CEFDBHGA";
	int n  = strlen(ps);
	root = CreateTreePI(ps,is,n);
	PreOrder(root);
	cout<<endl;
	NicePreOrder(root);
	cout<<endl;
	NiceInOrder(root);
	cout<<endl;
	InOrder(root);
	cout<<endl;
	NiceLevelOrder(root);
	cout<<endl;
	LevelOrder(root);
	cout<<endl;
}
