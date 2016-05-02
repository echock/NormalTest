#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip>
#include<stack>    // 
#include<queue>
#include<time.h>
using namespace std;
/*�ݹ�汾��˼�룺��������Ԫ�طֳɴ�С����
��ͬ�������Ӽ��ϣ��ֱ�������Ӽ��Ͻ�������
���ս��ź�����Ӽ��Ϻϲ�����Ҫ����ź����
����*/
template<class Type>
void Print(Type *ar,int n)
{
	for(int i =0;i<n;++i)
	{
		cout<<ar[i]<<" ";
	}
	cout<<endl;
}
template<class Type>
void Copy(Type *sd,Type *si,int left,int right)
{
	for(int i = left; i<=right; ++i)
	{
		sd[i] = si[i];
	}
}
template<class Type>
void Merge(Type *sd,Type *si,int left,int m,int right)
{
	int i = left, j = m+1;
	int k = left;
	while(i<=m && j<=right)
	{
		sd[k++]= si[i]<si[j]? si[i++]:si[j++];
	}
	while(i<=m)
	{
		sd[k++] =si[i++];
	}
	while(j<=right)
	{
		sd[k++] =si[j++];
	}
}
template<class Type>
void MergePass(Type *sd,Type *si,int left,int right)
{
	if(left<right)//����������Ԫ��
	{
		int m = ((right-left)>>1) + left;//ȡ�е�
		MergePass(sd,si,left,m);
		MergePass(sd,si,m+1,right);
		Merge(sd,si,left,m,right);//�ϲ�������sd
		Copy(si,sd,left,right);//���ƻ�����
	}
}

template<class Type>
void MergeSort(Type *ar,int n)
{
	Type *br = new Type[n];
	MergePass(br,ar,0,n-1);
	delete []br;
}
void main()
{
	int ar[]={12,34,78,89,90,100,67,56,34,45,93,18};
	int n = sizeof(ar)/sizeof(ar[0]);
	Print(ar,n);
	MergeSort(ar,n);
	Print(ar,n);
}
