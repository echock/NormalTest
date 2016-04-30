#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

//��ӡ����
template<class Type>
void Print(Type *ar,int n)
{
	for(int i = 0;i<n;i++)
		cout<<ar[i]<<" ";
	cout<<endl;
}

/*
���������鰴�տ��ŵ�˼�����򣬷��طֽ��ߵ�λ��
�ֽ���֮ǰ�Ķ����������С��֮��Ķ�������
*/
template<class Type>
int Partition(Type*ar,int left,int right)
{
	int i = left,j = right;
	Type tmp= ar[i];
	while(i<j)
	{
		while(i<j&&ar[j]>=tmp) 
	   //�Ӻ���ǰ�ұȷָ�����С��
			--j;
		//if(i<j)
			ar[i] = ar[j];
		while(i<j&&ar[i]<=tmp)
		//��ǰ�����ұȷָ����ִ��
			++i;
		//if(i<j)
			ar[j] = ar[i];
	}
	ar[i] = tmp;//��һ���ǵ�д
	return i;
}

//Ѱ�ҵ�k������ֵ����ַ�����������һ����
template<class Type>
const Type & SelectK1(Type *ar,int left,int right,int k)
{
	if(right == left && k == 1) return ar[left];
	int m = Partition(ar,left,right);
	int j = m-left +1;
	if(k == j)
		return ar[m];
	if(k<j)
		return SelectK1(ar,left,m-1,k);//��벿�ֵݹ�
	else
		return SelectK1(ar,m+1,right,k-j);//�Ұ벿�ݵݹ�
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