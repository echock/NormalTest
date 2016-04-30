#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

//打印数组
template<class Type>
void Print(Type *ar,int n)
{
	for(int i = 0;i<n;i++)
		cout<<ar[i]<<" ";
	cout<<endl;
}

/*
将给定数组按照快排的思想排序，返回分界线的位置
分界线之前的都比这个数字小，之后的都比它大
*/
template<class Type>
int Partition(Type*ar,int left,int right)
{
	int i = left,j = right;
	Type tmp= ar[i];
	while(i<j)
	{
		while(i<j&&ar[j]>=tmp) 
	   //从后往前找比分割数字小的
			--j;
		//if(i<j)
			ar[i] = ar[j];
		while(i<j&&ar[i]<=tmp)
		//从前往后找比分割数字大的
			++i;
		//if(i<j)
			ar[j] = ar[i];
	}
	ar[i] = tmp;//这一步记得写
	return i;
}

//寻找第k大的数字的两种方法，道理是一样的
template<class Type>
const Type & SelectK1(Type *ar,int left,int right,int k)
{
	if(right == left && k == 1) return ar[left];
	int m = Partition(ar,left,right);
	int j = m-left +1;
	if(k == j)
		return ar[m];
	if(k<j)
		return SelectK1(ar,left,m-1,k);//左半部分递归
	else
		return SelectK1(ar,m+1,right,k-j);//右半部份递归
}
template<class Type>
const Type & SelectK2(Type *ar,int left,int right,int k)
{
	if(right == left && k == 1) return ar[left];
	int m = Partition(ar,left,right);
	if(m+1==k)  return ar[m];
	if(m+1>k)
	{
		return SelectK2(ar,left,m-1,k);
	}
	else
	{
		return SelectK2(ar,m+1,right,k);
	}
}
template<class Type>
const Type & SelectKMin(Type *ar,int n, int k)
{
	if(ar == NULL || n < 1 || k < 1 || k>n)
		exit(1);
	else
		return SelectK2(ar,0,n-1,k);
}


void main()
{
	int ar[]={12,23,45,67,32,78,100,98,88,13};
	int n = sizeof(ar)/sizeof(ar[0]);
	int k;
	cin>>k;
	int x = SelectKMin(ar,n,k);
	cout<<k<<"=>"<<x<<endl;
	Print(ar,n);
}