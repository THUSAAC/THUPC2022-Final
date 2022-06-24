#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<r;++i)
#define Fe(i,l,r) for(int i=l;i<=r;++i)
typedef unsigned u32;
namespace IO{
const int BUF_SZ=1<<16;
char ib[BUF_SZ+1],*ip=ib+BUF_SZ;
void ipre(int n){
	int c=ib+BUF_SZ-ip;
	if(c<n){
		memcpy(ib,ip,c);
		ip=ib;
		fread(ib+c,1,BUF_SZ-c,stdin)[ib+c]=0;
	}
}
template<class T=int>
T read(T L,T R){
	ipre(100);
	T x=0,f=1;
	while(*ip<'0'||*ip>'9')if(*ip++=='-')f=-f;
	while(*ip>='0'&&*ip<='9')x=x*10+*ip++-'0';
	x*=f;
	if(!(L<=x&&x<=R)){
		std::cerr<<x<<" not in ["<<L<<","<<R<<"]\n";
		exit(1);
	}
	return x;
}
char ob[BUF_SZ+1],*op=ob;
void opre(int n){
	int c=ob+BUF_SZ-op;
	if(c<n){
		fwrite(ob,1,BUF_SZ-c,stdout);
		op=ob;
	}
}
template<class T>
void write(T x){
	opre(100);
	char ss[100],*sp=ss;
	if(x<T(0))x=-x,*op++='-';
	do *sp++=x%10+'0';while(x/=10);
	while(sp!=ss)*op++=*--sp;
}
template<class T>
void write(T x,char c){
	write(x);
	*op++=c;
}
struct __{
	__(){}
	~__(){
		fwrite(ob,1,op-ob,stdout);
	}
}_;
};
const int maxn=1e6,maxm=5e6,N=maxn+10,M=maxm+10;
struct Q{
	int l,r,id;
	bool operator<(const Q &q)const{return r<q.r;}
}qs[M],qs2[M];

u32 gcd(u32 a,u32 b){
	return b?gcd(b,a%b):a;
}

u32 a[N],b[N],c[N],ans[M];
struct D{
	u32 s,ss;
	int t;
	void upd(u32 v,int t0){
		ss+=s*(t0-t);
		s=v;
		t=t0;
	}
	u32 que(int t0){
		return ss+s*(t0-t);
	}
}d[N];

template<class T,class F>
void rsort(T *d0,T *d1,int n,int v,F key){
	static int t[1<<20];
	F(i,0,v)t[i]=0;
	F(i,0,n)++t[key(d0[i])];
	int s=0;
	F(i,0,v){
		int a=t[i];
		t[i]=s;
		s+=a;
	}
	F(i,0,n)d1[t[key(d0[i])]++]=d0[i];
}

int main(){
	using namespace IO;
	int n=read(1,maxn);
	int m=read(1,maxm);
	Fe(i,1,n)a[i]=read(1,n);
	Fe(i,1,n)b[i]=read(1,n);
	Fe(i,1,n)c[i]=read(1,n);
	F(i,0,m){
		int l=read(1,n),r=read(l,n);
		qs[i]=Q{l,r,i};
	}
	rsort(qs,qs2,m,1024,[](Q &q){return q.r&1023;});
	rsort(qs2,qs,m,1024,[](Q &q){return (q.r>>10)&1023;});
	int p=0;
	Fe(r,1,n){
		u32 v=a[r];
		int pa=r-1;
		for(;pa;--pa){
			u32 &t=a[pa],t1=t&v;
			if(t1==t)break;
			t=t1;
		}
		v=b[r];
		int pb=r-1;
		for(;pb;--pb){
			u32 &t=b[pb],t1=t|v;
			if(t1==t)break;
			t=t1;
		}
		v=c[r];
		int pc=r-1;
		for(;pc;--pc){
			u32 &t=c[pc],t1=gcd(v,t);
			if(t1==t)break;
			t=t1;
		}
		d[r].ss=d[r-1].que(r);
		Fe(i,std::min(pa,std::min(pb,pc))+1,r){
			d[i].upd(a[i]*b[i]*c[i]+d[i-1].s,r);
		}
		u32 sr=d[r].que(r+1);
		for(;p<m&&qs[p].r==r;++p){
			int l0=qs[p].l-1;
			ans[qs[p].id]=sr-d[l0].que(r+1);
		}
	}
	F(i,0,m)write(ans[i],'\n');
	return 0;
}