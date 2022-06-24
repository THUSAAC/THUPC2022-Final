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
const int maxn=1e6,maxm=5e6,N=maxn+10;
struct Q{
	int l,r,id;
	bool operator<(const Q &q)const{return r<q.r;}
}qs[N];
u32 a[N],b[N],c[N],s[N],ans[N];
u32 gcd(u32 a,u32 b){
	return b?gcd(b,a%b):a;
}
int main(){
	int n=read(1,maxn);
	int m=read(1,maxm);
	Fe(i,1,n)a[i]=read(1,n);
	Fe(i,1,n)b[i]=read(1,n);
	Fe(i,1,n)c[i]=read(1,n);
	F(i,0,m){
		int l=read(1,n),r=read(l,n);
		qs[i]=Q{l,r,i};
	}
	std::sort(qs,qs+m);
	int p=0;
	Fe(r,1,n){
		u32 sa=~0u,sb=0,sc=0,s3=0;
		for(int i=r;i>=1;--i){
			sa&=a[i];
			sb|=b[i];
			sc=gcd(sc,c[i]);
			s3+=sa*sb*sc;
			s[i]+=s3;
			//pr("[%d,%d]:%u %u %u\n",i,r,sa*sb*sc,s3,s[i]);
		}
		for(;p<m&&qs[p].r==r;++p){
			ans[qs[p].id]=s[qs[p].l];
		}
	}
	F(i,0,m)printf("%u\n",ans[i]);
	return 0;
}