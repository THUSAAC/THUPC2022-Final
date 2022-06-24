#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<r;++i)
#define Fe(i,l,r) for(int i=l;i<=r;++i)
#define pr(...) fprintf(stderr,__VA_ARGS__)
typedef long long i64;
int read(int L,int R){
	int x;
	assert(scanf("%d",&x)==1);
	assert(L<=x&&x<=R);
	return x;
}
const int maxn=1e6,maxm=1e6,N=maxn+10,M=maxm+10;

int a[N];
i64 b[N];

int main(){
	int n=read(1,maxn);
	int m=read(1,maxm);
	Fe(i,1,n)a[i]=read(1,n);
	F(i,0,m){
		int o=read(1,2);
		if(o==1){
			int l=read(1,n),r=read(l,n);
			Fe(q,l,r){
				Fe(p,l,q){
					if(a[p]<=a[q])++b[q];
				}
			}
		}else{
			int x=read(1,n);
			printf("%lld\n",b[x]);
		}
	}
	return 0;
}