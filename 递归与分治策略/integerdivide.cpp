#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip>
#include<stack>    // 
#include<queue>
#include<time.h>
using namespace std;
int q(int n,int m)
{
	if(n == 1 || m == 1) return 1;
	if(m > n) return q(n,n);
	if(m == n) return q(n,n-1)+1;
	else return q(n,m-1)+q(n-m,m);
}
void main()
{
	int n,m;
	cin>>n>>m;
	cout<<q(n,m)<<endl;
}

