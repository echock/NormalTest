#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip>
#include<stack>    // 
#include<queue>
#include<time.h>
using namespace std;

#define SIZE 8
typedef int Array[SIZE][SIZE];
//¥Ú”°∆Â≈Ã
void Print(Array a)
{
	for(int i = 0;i<SIZE;++i)
	{
		for(int j = 0;j<SIZE;++j)
		{
			cout<<setw(4)<<a[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
}
int tile = 1;//»´æ÷±‰¡øπ«≈∆
void CheseBoard(Array ar,int tr,int tc,int dr,int dc,int size)
{
	if(size<=1)
		return ;
	int t= tile++;
	int s = size>>1;

	//∏≤∏«◊Û…œΩ«◊”∆Â≈Ã
	if(dr<tr+s&&dc<tr+s)
		CheseBoard(ar,tr,tc,dr,dc,s);
	else
	{
		ar[tr+s-1][tc+s-1] = t;
		CheseBoard(ar,tr,tc,tr+s-1,tc+s-1,s);
	}
	
	//∏≤∏«”“…œΩ«◊”∆Â≈Ã
	if(dr < tr+s && dc >= tc+s)
		CheseBoard(ar,tr,tc+s,dr,dc,s);
	else
	{
		ar[tr+s-1][tc+s] = t;
		CheseBoard(ar,tr,tc+s,tr+s-1,tc+s,s);
	}

	//∏≤∏«”“œ¬Ω«◊”∆Â≈Ã
	if(dr >= tr+s && dc >= tc+s)
		CheseBoard(ar,tr+s,tc+s,dr,dc,s);
	else
	{
		ar[tr+s][tc+s] = t;
		CheseBoard(ar,tr+s,tc+s,tr+s,tc+s,s);
	}

	//∏≤∏«◊Ûœ¬Ω«◊”∆Â≈Ã
	if(dr >=tr+s && dc <tc+s)
		CheseBoard(ar,tr+s,tc,dr,dc,s);
	else
	{
		ar[tr+s][tc+s-1] = t;
		CheseBoard(ar,tr+s,tc,tr+s,tc+s-1,s);
	}
	Print(ar);
}
void main()
{
	Array ar={0};
	int dr,dc;
	cin>>dr>>dc;
	ar[dr][dc] = -1;
	Print(ar);
	CheseBoard(ar,0,0,dr,dc,SIZE);
	Print(ar);
}
