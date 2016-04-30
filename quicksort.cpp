#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip>
#include<stack>    // 
#include<queue>
#include<time.h>
using namespace std;

template<class Type>
void Print(Type *ar,int n)
{
	for(int i = 0;i<n;i++)
		cout<<ar[i]<<" ";
}
//分割，左边比它小，右边相反
template<class Type>
int Partition(Type*ar,int left,int right)
{
	Type tmp = ar[left];
	int i = left,j = right;
	while(i<j)
	{
		while(i<j&&ar[j]>=tmp)
			--j;
		if(i<j)
			ar[j] = ar[i];
		while(i<j&&ar[i]<=tmp)
			++i;
		if(i<j)
			ar[i] = ar[j];
	}
	ar[i] = tmp;
	return i;
}
template<class Type>
void QuickPass(Type*ar,int left,int right)
{
	if(left<right)
	{
		int m = Partition(ar,left,right);
		QuickPass(ar,left,m);
		QuickPass(ar,m+1,right);
	}
}
template<class Type>
void QuickSort(Type*ar,int n)
{
	if(ar==NULL||n<=0)
		return ;
	QuickPass(ar,0,n-1);
}
void main()
{
	int ar[]={56,12,34,78,89,90,100,67,45,23};
	int n = sizeof(ar)/sizeof(ar[0]);
	Print(ar,n);
	QuickSort(ar,n);
	Print(ar,n);
}