#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<r;++i)
#define Fe(i,l,r) for(int i=l;i<=r;++i)
#define Fer(i,l,r) for(int i=l;i>=r;--i)

const int MEM=1<<26;
char pool[MEM],*pool_p=pool;

template<class T>
void alloc(T *&p,int sz){
	p=reinterpret_cast<T*>(pool_p);
	pool_p+=sz*sizeof(T);
	assert(pool_p<pool+MEM);
	F(i,0,sz)new(p+i)T();
}

template<class T>
struct Undo{
	T &x;
	T x0;
	Undo(T &x):x(x),x0(x){}
	~Undo(){x=x0;}
};

#define alloc_scope Undo<char*> _##__LINE__(pool_p)

template<class T>
struct BIT{
	T *a;
	int n;
	void alloc(int n0){
		n=n0;
		::alloc(a,n+1);
	}
	void add(int x,T y){
		int _n=n;
		for(;x<=_n;x+=x&-x)a[x]+=y;
	}
	T sum(int x){
		T s=0;
		for(;x;x-=x&-x)s+=a[x];
		return s;
	}
	void dna(){
		Fe(i,1,n)a[i]+=a[i-(i&-i)];
	}
	T at(int x){
		return a[x];
	}
};

typedef long long i64;
int read(int L,int R){
	int x;
	assert(scanf("%d",&x)==1);
	assert(L<=x&&x<=R);
	return x;
}
const int maxn=2e5,maxm=1e6,N=maxn+1110,sN=500,ssN=24,M=maxm+1110;

struct XY{
	int x,y;
	bool operator<(const XY &w)const{return y<w.y;}
}xy[N];
std::vector<XY> xy2[sN];

i64 b[N];

template<class T,unsigned n1,unsigned n2,unsigned bsz=4>
struct ZGrid{
	T v[n1/bsz+1][n2][bsz];
	T &operator()(unsigned x,unsigned y){
		return v[x/bsz][y][x%bsz];
	}
};

ZGrid<int,sN,N> v1,v2;
ZGrid<int,sN,sN> v3;
int sx[N],ys[N],yr[N];
const int B1=22,B2=B1*B1;
struct PARS{
	int s22[sN][sN],s23[sN][ssN],s32[ssN][sN],s33[ssN][ssN];
	void inc(int x2,int y2,int a){
		int x3=x2/B1,y3=y2/B1;
		s22[x2][y2]+=a;
		s23[x2][y3]+=a;
		s32[x3][y2]+=a;
		s33[x3][y3]+=a;
	}
	int sum(int x2,int y2){
		int s=0;
		int x3=x2/B1,y3=y2/B1;
		#define Fi3 F(i,0,x3)
		#define Fi2 F(i,x3*B1,x2)
		#define Fj3 F(j,0,y3)
		#define Fj2 F(j,y3*B1,y2)
		Fi3 Fj3 s+=s33[i][j];
		Fi2 Fj2 s+=s22[i][j];
		Fi2 Fj3 s+=s23[i][j];
		Fi3 Fj2 s+=s32[i][j];
		return s;
	}
}rs1,rs2[sN];

void inc(int x,int a){
	rs1.inc(x/B2,ys[x]/B2,a);
	sx[x]+=a;
}

void inc(int x,int y,int a){
	rs1.inc(x/B2,y/B2,a);
	rs2[y/B2].inc(x/B2,y%B2,a);
}
int sum(int x){
	int y=ys[x];
	int x2=x/B2,y2=y/B2;
	int s=rs1.sum(x2,y2);
	s+=rs2[y2].sum(x2,y%B2+1);
	Fe(i,x2*B2,x)if(ys[i]<=y)s+=sx[i];
	Fe(j,y2*B2,y)if(yr[j]<x2*B2)s+=sx[yr[j]];
	return s;
}

int main(){
	int n=read(1,maxn);
	int m=read(1,maxm);
	int B=sqrt(n)+2;
	Fe(x,1,n){
		int y=read(1,n);
		xy[x]=XY{x,y};
		xy2[x/B2].push_back(xy[x]);
		yr[ys[x]=y]=x;
	}
	
	Fe(i,0,n/B2)std::sort(xy2[i].begin(),xy2[i].end());
	
	for(int l=1,r=B,bid=1;l<=n;l+=B,r+=B,++bid){
		alloc_scope;
		
		BIT<int> bit;
		bit.alloc(n);
		
		r=std::min(r,n);
		Fe(i,l,r){
			bit.add(ys[i],1);
			v1(bid,i)=bit.sum(ys[i]);
		}
		bit.dna();
		Fe(i,r+1,n){
			v1(bid,i)=bit.at(ys[i]);
		}
		std::sort(xy+l,xy+r+1);
	}
	
	F(i,0,m){
		int o=read(1,2);
		if(o==1){
			int l=read(1,n),r=read(l,n);
			int L=(l-1)/B+1,R=(r-1)/B+1;
			auto _add=[=](int R,int r,int a){
				int r0=r/B2;
				F(i,0,r0)v3(R,i)+=a;
				Fe(i,r0*B2,r)v2(R,i)+=a;
			};
			int Lb=(L-1)*B+1,Le=std::min(n,L*B);
			_add(R+1,r,-1);
			auto _radd=[=](int l,int r,int x,int s){
				r=std::min(r,x);
				int p=Lb,cnt=0;
				for(XY w:xy2[(x+1)/B2]){
					if(w.x<=x)continue;
					for(;p<=Le;++p){
						int y0=xy[p].y;
						if(y0>w.y)break;
						int x0=xy[p].x;
						if(l<=x0&&x0<=r)++cnt;
					}
					b[w.x]+=cnt*-s;
				}
				Fe(i,l,r){
					inc(i,s);
					inc(x+1,ys[i],-s);
				}
			};
			if(l-Lb<B/2){
				_add(L,r,1);
				_radd(Lb,l-1,r,-1);
			}else{
				_add(L+1,r,1);
				_radd(l,Le,r,1);
			}
		}else{
			int x=read(1,n);
			int X=(x-1)/B+1;
			int s=0;
			i64 ans=b[x];
			ans+=sum(x);
			Fe(i,1,X){
				s+=v3(i,x/B2)+v2(i,x);
				ans+=i64(s)*v1(i,x);
			}
			printf("%lld\n",ans);
		}
	}
	
	return 0;
}