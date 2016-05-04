#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip>
#include<stack>    
#include<queue>
#include<time.h>
using namespace std;
template<class Type>
void Swap(Type&a,Type&b)
{
	Type tmp = a;
	a = b;
	b = tmp;
}
template<class Type>
void Perm(Type*ar,int k,int m)
{
	if(k == m) 
	{
		for(int i = 0;i<=m;++i)
		{
			cout<<ar[i]<<" ";
		}
		cout<<endl;
	
	}else
	{
		for(int j = k;j<=m;++j)
		{
			Swap(ar[k],ar[j]);
			Perm(ar,k+1,m);
			Swap(ar[k],ar[j]);
		}
	}
}
void main()
{
	int R[]={1,2,3,4,5};
	int n = sizeof(R)/sizeof(R[0]);
	Perm(R,0,n-1);
}