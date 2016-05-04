#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip>
#include<stack>    // 
#include<queue>
#include<time.h>
using namespace std;
/*
今天学了小根堆，所以，我准备写个大根堆

*/
#define HEAPSIZE 100
template<class Type>
class MaxHeap
{
	Type *heap;
	int cursize;
	int maxsize;
	static void FilterDown(Type *ar,const int start,const int end)
	{
		int i = start,j = i*2;
		while(j<=end)
		{
			if(j<end&&ar[j]<ar[j+1])
				j+=1;
			if(ar[0]>=ar[j])
				break;
			ar[i] = ar[j];
			i = j;
			j = 2*i;
		}
		ar[i] = ar[0];
	}
	static void MakeHeap(Type *ar,int n)
	{
		int pos = n/2;
		while(pos >=1)
		{
			FilterDown(ar,pos,n);
			--pos;
		}
	}
	static void FilterUp(Type *ar,const int start,const int end)
	{
		int j = start, i = j/2;
		ar[0] = ar[j];
		while(i >= end)
		{
			if(ar[0] <= ar[i]) break;
			ar[j] = ar[i];
			j = i;
			i = j/2;
		}
		ar[j] = ar[0];
	}

public:
	bool Insert(const Type &x)
	{
		if(full()) return false;
		heap[++cursize] = x;
		FilterUp(heap,cursize,1);
		return true;
	}
	MaxHeap(int sz = HEAPSIZE)
	{
		maxsize = sz > HEAPSIZE? sz:HEAPSIZE;
		cursize = 0;
		heap = (Type*)malloc(sizeof(Type)*(maxsize+1));
	}
	MaxHeap(Type *ar,int n)
	{
		maxsize = n > HEAPSIZE? n:HEAPSIZE;
		cursize = n;
		heap = (Type *)malloc(sizeof(Type)*(maxsize+1));
		for(int i = 0;i<n;++i)
		{
			heap[i+1] = ar[i];
		}
		MakeHeap(heap,cursize);
	}
	~MaxHeap()
	{
		free(heap);
		heap = NULL;
		cursize = 0;
		maxsize = 0;
	}
	int size() const { return cursize;}
	bool empty() const { return size() == 0;}
	bool full() const { return size() == maxsize;}

	bool Remove(Type &x)
	{
		if(empty()) return false;
		x = heap[1];
		heap[1] = heap[cursize--];
		FilterDown(heap,1,cursize);
		return true;
	}
	
};
void main()
{
	int ar[]={67,45,89,34,23,10,90,100,18,56};
	int n = sizeof(ar)/sizeof(ar[0]);
	MaxHeap<int> mh;
	for(int i = 0;i<n;++i)
	{
		mh.Insert(ar[i]);
	}
	int x ;
	while(mh.Remove(x))
	{
		cout<<x<<"  ";
	}
	cout<<endl;
}