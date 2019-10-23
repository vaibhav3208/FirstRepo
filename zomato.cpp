#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define ll long long int 
ll n,q;
ll A[100004];
ll B[31][100004],C[31][100004];
ll B_Tree[31][100004],C_Tree[31][100004];

ll getSum(ll BITree[31][100004], ll row, ll index) 
{ 
    ll sum = 0; 
    index = index + 1; 
    while (index>0) 
    { 
        sum += BITree[row][index]; 
      index -= index & (-index); 
    } 
    return sum; 
} 

void updateBIT(ll BITree[31][100004], ll n, ll row, ll index, ll val) 
{  
    index = index + 1; 
    while (index <= n) 
    { 
    BITree[row][index] += val; 
    index += index & (-index); 
    } 
} 
int main()
{
	cin>>n>>q;
	for(ll i=0;i<n;i++)
	{
		cin>>A[i];
		ll x;
		if(A[i]==0)
		{
			B[1][i]=1;
		}
		else
		{
			x=(ll)(log2(A[i]))+1;
			x=x-__builtin_popcount(A[i]);
			B[x][i]=1;
			x=__builtin_popcount(A[i]);
			C[x][i]=1;
		}
	}
	for(ll i=0;i<31;i++)
	{
		for(ll j=0;j<n;j++)
		{
			updateBIT(B_Tree, n, i, j, B[i][j]); 
			updateBIT(C_Tree, n, i, j, C[i][j]); 
		}
	}
	while(q--)
	{
		ll type,l,r;
		cin>>type>>l>>r;
		if(type==1)
		{
			if(A[l-1]==0)
			{
				updateBIT(B_Tree, n, 1, l-1, -1);
			}
			else
			{
				ll x=(ll)(log2(A[l-1]))+1;
				x=x-__builtin_popcount(A[l-1]);
				if(B[x][l-1]==1)
				updateBIT(B_Tree, n, x, l-1, -1);
				B[x][l-1]=0;
				x=__builtin_popcount(A[l-1]);
				if(C[x][l-1]==1)
				updateBIT(C_Tree, n, x, l-1, -1);
				C[x][l-1]=0;
			}
			if(r==0)
			{
				updateBIT(B_Tree, n, 1, l-1, 1);	
			}
			else
			{
				x=(ll)(log2(r))+1;
			   	x=x-__builtin_popcount(r);
				if(B[x][l-1]==0)
				updateBIT(B_Tree, n, x, l-1, 1);
				B[x][l-1]=1; 
				x=__builtin_popcount(r);
				if(C[x][l-1]==0)
				updateBIT(C_Tree, n, x, l-1, 1);
				C[x][l-1]=1;
				A[l-1]=r;			
			}

		}
		else if (type==2)
		{
			ll ans=1;
			for(ll i=0;i<31;i++)
			{
				ll count=getSum(B_Tree,i,r-1)-getSum(B_Tree,i,l-2);
				if(count>0)ans=((ans%MOD)*(count%MOD))%MOD;
			}
			cout<<ans<<'\n';
		}
		else if (type==3)
		{
			ll ans=1;
			for(ll i=0;i<31;i++)
			{
				ll count=getSum(C_Tree,i,r-1)-getSum(C_Tree,i,l-2);
				if(count>0)ans=((ans%MOD)*(count%MOD))%MOD;
			}
			cout<<ans<<'\n';
		}
	}
}