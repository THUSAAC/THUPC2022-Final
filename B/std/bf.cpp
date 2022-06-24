#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<r;++i)
#define Fe(i,l,r) for(int i=l;i<=r;++i)
#define pr(...) fprintf(stderr,__VA_ARGS__)
typedef unsigned u32;
int read(int L,int R){
	int x;
	assert(scanf("%d",&x)==1);
	assert(L<=x&&x<=R);
	return x;
}
const int maxn=1e6,maxm=2e6,N=maxn+10,M=maxm+10,maxv=1e9;
typedef long long i64;
int a[N],b[N];
bool ed[N];
int main(){
	int n=read(1,maxn);
	int m=read(1,maxm);
	Fe(i,1,n)a[i]=read(1,n);
	Fe(i,1,n){
		b[i]=read(1,n);
		assert(!ed[b[i]]);
		ed[b[i]]=1;
	}
	F(i,0,m){
		int o=read(1,2);
		if(o==1){
			int x=read(1,n),y=read(1,n);
			a[x]=y;
		}else{
			int l=read(1,n),r=read(l,n),x=read(1,n),ans=0;
			for(int i=l;i<=r;){
				int j=i;
				bool hx=(a[i]==x);
				while(j+1<=r&&a[j+1]==b[a[j]])hx|=(a[++j]==x);
				if(hx)ans=std::max(ans,j+1-i);
				i=j+1;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}