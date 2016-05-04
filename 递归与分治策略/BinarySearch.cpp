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
int FindValue(Type *ar,int n, const Type &x)
{
	if(ar == NULL || n < 1) return -1; // 
	int left = 0, right = n-1;
	while(left <= right) // left<right///
	{
		int mid = ((right-left)>>1) +left;///
		if(ar[mid] == x)
		{
			while(ar[mid-1] == x) mid-=1;///
			return mid;
		}
		if(x < ar[mid]) right = mid-1;
		else left = mid+1;
	}
	return -1;
}

template<class Type>
int Search(Type *ar,int left, int right,const Type &x)
{
	if(left <= right) // left<right///
	{
		int mid = ((right-left)>>1) +left;///
		if(ar[mid] == x)
		{
			while(ar[mid-1] == x) mid-=1;///
			return mid;
		}
		if(x < ar[mid]) return Search(ar,left,mid-1,x);
		else return Search(ar,mid+1,right,x);
	}else
	{
		return -1;
	}
}
template<class Type>
int SearchValue(Type *ar,int n, const Type &x)
{
	if(ar == NULL || n < 1) return -1;
	return Search(ar,0,n-1,x);
}
void main()
{
	int ar[]={12,23,34,45,45,45,45,45,56,67,78,89,90,100,110};
	int n = sizeof(ar)/sizeof(ar[0]);
	int x;
	cin>>x;
	int pos = FindValue(ar,n,x);
	cout<<pos<<" "<<endl;

	pos = SearchValue(ar,n,x);
	cout<<pos<<" "<<endl;
}