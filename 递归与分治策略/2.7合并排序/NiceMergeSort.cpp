#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip>
#include<stack>    // 
#include<queue>
#include<time.h>
using namespace std;
/*分治策略消除递归
首先将数组a中相邻元素两两排序。用合并算法将它们
排序，构成2/n组长度为2的排好序的子数组段，然后在将
它们排序成长度为4的排好序的子数组段，如此继续下去，
直至整个数组排好序

*/
template<class Type>
void Print(Type*ar,int n)
{
	for (int i = 0;i<n;i++)
		cout<<ar[i]<<" ";
	cout<<endl;
}
template<class Type>
void Merge(Type sd,Type si,int left,int m,int right)
{
	int k = left;
	int i = left, j = m+1;
	while(i<=m&&j<=right)
	{
		sd[k++] = si[i]>si[j]?si[j++]:si[i++];
	}
	while(i<=m)
		sd[k++] = si[i++];
	while(j<=right)
		sd[k++] = si[j++];
}
template<class Type>
void MergePass(Type*sd,Type*si,int s,int n)
{
	for (int i = 0;i+2*s<=n;i+=s*2)
	{
		Merge(sd,si,i,i+s-1,i+2*s-1);
	}
	if(n-1>=i+s)
	{
		Merge(sd,si,i,i+s-1,n-1);
//the left is not enough to merge bur is needed to be sorted
	}
	else
	{
		for(int j = i;j<n;++j)
			sd[j] = si[j];
//the left is not enough but is sorted
	}
}
template<class Type>
void MergeSort(Type*ar,int n)
{
	int s = 1;
	Type *br = new Type[n];
	while(s<n)
	{
		MergePass(br,ar,s,n);
		s+=s;
		MergePass(ar,br,s,n);
		s+=s;
	}
	delete []br;
}
void main()
{
	int ar[]={12,23,45,32,67,88,13,99,78};
	int n = sizeof(ar)/sizeof(ar[0]);
	Print(ar,n);
	MergeSort(ar,n);
	Print(ar,n);
}
