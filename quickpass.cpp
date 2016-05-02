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
由于超级好奇快排的效率，我测试了十万个数字
然后用静态变量记录了分割时候发生的比较次数。
然后，数字是70w多，天啦噜
*/
//打印数组
template<class Type>
void Print(Type *ar,int n)
{
	for(int i = 0;i<n;i++)
		cout<<ar[i]<<" ";
	cout<<endl;
}

//交换数字
template<class Type>
void Swap(Type &left,Type &right)
{
	int tmp = left;
	left =right;
	right = tmp;
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
			j--;
		if(i<j)
			ar[i] = ar[j];
		while(i<j&&ar[i]<=tmp)
			i++;
		if(i<j)
			ar[j] = ar[i];
	}
	ar[i] = tmp;
	return i;
}
//随机快速排序
template<class Type>
int RandPartition(Type*ar,int left,int right)
{
	srand(time(NULL));
	int pos = rand()%(right-left+1)+left;
	Swap(ar[left],ar[pos]);
	return Partition(ar,left,right);
}

//快速排序
template<class Type>
void QuickPass(Type*ar,int left,int right)
{
	if(left<right)
	{
		int m = RandPartition(ar,left,right);
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
	/*int ar[]={56,12,34,78,89,90,100,67,45,23};
	int n = sizeof(ar)/sizeof(ar[0]);
	Print(ar,n);
	QuickSort(ar,n);
	Print(ar,n);*/
	int ar[100000]={0};
	for (int i = 0;i<100000;i++)
		ar[i] = rand();
	int n = sizeof(ar)/sizeof(ar[0]);
	Print(ar,n);
	cout<<"ahhhhhhhhhhhhhhhhhhhh"<<endl;
	cout<<"ahhhhhhhhhhhhhhhhhhhh"<<endl;
	cout<<"ahhhhhhhhhhhhhhhhhhhh"<<endl;
	cout<<"ahhhhhhhhhhhhhhhhhhhh"<<endl;
	QuickSort(ar,n);
	Print(ar,n);
	cout<<num<<endl;
}