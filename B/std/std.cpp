#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<r;++i)
#define Fe(i,l,r) for(int i=l;i<=r;++i)
#define pr(...) void(0)//fprintf(stderr,__VA_ARGS__)

const int MEM=1<<30;
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

struct Void{
	char _[0];
	template<class T>
	void operator*=(const T &x){}
	template<class T>
	friend void operator*=(T &x,Void y){}
	friend Void operator+(Void a,Void b){return Void();}
};

template<class D=Void,class M=Void>
struct MSegTree{
	struct Node{
		D d;
		M m;
		void up(const Node &a,const Node &b){
			d=a.d+b.d;
			d*=m;
		}
	}*tr;
	int mx;
	int n;
	void in(int x){assert(1<=x&&x<=n);}
	void in(int l,int r){assert(1<=l&&l<=r&&r<=n);}
	void alloc(int n){
		for(mx=1;mx<n+2;mx<<=1);
		::alloc(tr,mx+n+3);
		this->n=n;
	}
	void up(int x){
		tr[x].up(tr[x*2],tr[x*2+1]);
	}
	template<class T>
	void update(int x,T y){
		in(x);
		for(tr[x+=mx].d=y;x>1;up(x>>=1));
	}
	D query(int l,int r){
		in(l),in(r);
		D a1,a2;
		for(l+=mx-1,r+=mx+1;l^r^1;a1*=tr[l>>=1].m,a2*=tr[r>>=1].m){
			if(~l&1)a1=a1+tr[l+1].d;
			if(r&1)a2=tr[r-1].d+a2;
		}
		a1=a1+a2;
		for(;l>1;a1*=tr[l>>=1].m);
		return a1;
	}
};

int read(int L,int R){
	int x;
	assert(scanf("%d",&x)==1);
	assert(L<=x&&x<=R);
	return x;
}
const int maxn=1e6,maxm=2e6,N=maxn+10,M=maxm+10,maxv=1e9;
typedef long long i64;
int a[N],b[N],rpos[N];
int ed[N],rid[N],rp;
int ans[N],ansp=0;


struct Q{
	int id,l,r,y;
};

struct Q2{
	int tp,l,r,x,v;
};
std::vector<Q2> qs2;
int rsz,n;


struct Max{
	using T=int;
	T x;
	Max(T x=0):x(x){}
	Max operator+(Max w)const{return std::max(x,w.x);}
};
MSegTree<Max> tr;

int ys[N];

struct Seg{
	mutable int l,r;
	bool operator<(const Seg &s)const{return r<s.r;}
	void del()const{
		ins(0);
	}
	void ins(int tp=1)const{
		int L=ys[l],R=ys[r];
		int len=r-l+1;
		if(len>=rsz)L=1,R=rsz;
		len*=tp;
		if(L<=R){
			qs2.push_back(Q2{0,L,R,l,len});
		}else{
			qs2.push_back(Q2{0,L,rsz,l,len});
			qs2.push_back(Q2{0,1,R,l,len});
		}
	}
};
std::multiset<Seg> segs;

struct Ring{
	int sz;
	std::vector<Q> qs;
	void ins(int x,int y){
		qs.push_back(Q{0,x,1,y});
	}
	void del(int x,int y){
		qs.push_back(Q{0,x,0,y});
	}
	void que(int l,int r,int y){
		qs.push_back(Q{++ansp,l,r,y});
	}
	bool adj(int a,int b){
		return a==sz?b==1:(a?a+1==b:0);
	}
	bool ex(int y,int l,int r){
		assert(1<=y&&y<=sz);
		int y0=ys[l];
		assert(1<=y0&&y0<=sz);
		int d=y-y0;
		if(d<0)d+=sz;
		return d<=r-l;
	}
	void _ins(int x,int y){
		pr("_ins %d %d\n",x,y);
		assert(ys[x]==0);
		ys[x]=y;
		auto p2=segs.insert(Seg{x,x});
		auto p1=p2,p3=p2;
		--p1,++p3;
		bool f1=(p1->r+1==x&&adj(ys[x-1],ys[x]));
		bool f3=(p3->l-1==x&&adj(ys[x],ys[x+1]));
		if(f1){
			p1->del();
			if(f3){
				p3->del();
				p1->r=p3->r;
				segs.erase(p2);
				segs.erase(p3);
			}else{
				p1->r=x;
				segs.erase(p2);
			}
			p1->ins();
		}else if(f3){
			p3->del();
			p3->l=x;
			segs.erase(p2);
			p3->ins();
		}else{
			p2->ins();
		}
	}
	void _del(int x,int y){
		pr("_del %d %d\n",x,y);
		assert(ys[x]==y);
		auto p=segs.lower_bound(Seg{x,x});
		p->del();
		if(p->l==x){
			if(p->r==x){
				segs.erase(p);
			}else{
				p->l=x+1;
				p->ins();
			}
		}else if(p->r==x){
			p->r=x-1;
			p->ins();
		}else{
			Seg s{x+1,p->r};
			p->r=x-1;
			segs.insert(s);
			p->ins();
			s.ins();
		}
		ys[x]=0;
	}
	int _que(int l,int r,int y,int id){
		pr("_que [%d,%d] %d\n",l,r,y);
		int ans=0;
		auto p=segs.lower_bound(Seg{l,l});
		if(p->l<l){
			int L=l,R=std::min(p->r,r);
			if(ex(y,L,R))ans=std::max(ans,R-L+1);
			l=R+1;
		}
		if(l>r)return ans;
		p=segs.lower_bound(Seg{r+1,r+1});
		if(p->l<=r){
			int L=std::max(l,p->l),R=r;
			if(ex(y,L,R))ans=std::max(ans,R-L+1);
			r=L-1;
		}
		if(l>r)return ans;
		pr("rest [%d,%d]\n",l,r);
		qs2.push_back(Q2{1,l,r,y,id});
		return ans;
	}
	void dc(Q2 *qs,int qp,int L,int R){
		static int dep=0;
		static int sqp=0;
		int sqp0=sqp;
		++dep;
		sqp+=qp;
		
		pr("> dc [%d,%d]\n",L,R);
		alloc_scope;
		
		Q2 *qs1,*qs2;
		alloc(qs1,qp);
		alloc(qs2,qp);
		
		//fprintf(stderr,"[%d  %d  %d  %d]\n",dep,int((pool_p-pool)/sizeof(Q2)),sqp,qp);
		
		for(;;){
			int M=(L+R)>>1;
			int qp1=0,qp2=0;
			int qp1d=0,qp2d=0;
			int m_cnt=0;
			F(i,0,qp){
				Q2 &q=qs[i];
				if(q.tp==0){
					++m_cnt;
					if(q.r<L||q.l>R)assert(0);
					else if(q.l<=L&&R<=q.r){
						pr(">> upd [%d,%d] %d v=%d\n",q.l,q.r,q.x,q.v);
						tr.update(q.x,Max{q.v});
					}else{
						if(q.l<=M){
							qs1[qp1++]=q;
							if(q.r>=R)++qp2d;
						}
						if(q.r>M){
							qs2[qp2++]=q;
							if(q.l<=L)++qp1d;
						}
					}
				}else{
					int v=tr.query(q.l,q.r).x;
					pr(">> que [%d,%d] %d qid=%d ans=%d\n",q.l,q.r,q.x,q.v,v);
					ans[q.v]=std::max(ans[q.v],v);
					
					if(q.x<=M)qs1[qp1++]=q;
					else qs2[qp2++]=q;
				}
			}
			if(L<R){
				//fprintf(stderr,"%d %d => %d,%d\n",qp,m_cnt,qp1,qp2);
				if(qp1-qp1d<qp2-qp2d){
					dc(qs1,qp1,L,M);
					//dc(qs2,qp2,M+1,R);
					std::swap(qs2,qs);
					qp=qp2;
					L=M+1;
				}else{
					dc(qs2,qp2,M+1,R);
					//dc(qs1,qp1,L,M);
					std::swap(qs1,qs);
					qp=qp1;
					R=M;
				}
			}else break;
		}
		--dep;sqp=sqp0;
	}
	void cal(){
		qs2.clear();
		::rsz=sz;
		for(Q &q:qs){
			if(q.id){
				ans[q.id]=_que(q.l,q.r,q.y,q.id);
			}else if(q.r){
				_ins(q.l,q.y);
			}else{
				_del(q.l,q.y);
			}
		}
		
		dc(qs2.data(),qs2.size(),1,sz);
	}
}rs[N];

void ins(int x,int y){
	rs[rid[y]].ins(x,rpos[y]);
}
void del(int x,int y){
	rs[rid[y]].del(x,rpos[y]);
}
void que(int l,int r,int x){
	rs[rid[x]].que(l,r,rpos[x]);
}

int main(){
	n=read(1,maxn);
	int m=read(1,maxm);
	Fe(i,1,n)a[i]=read(1,n);
	Fe(i,1,n){
		b[i]=read(1,n);
		assert(!ed[b[i]]);
		ed[b[i]]=1;
	}
	segs.insert(Seg{0,0});
	segs.insert(Seg{n+1,n+1});
	Fe(i,1,n){
		if(rid[i])continue;
		++rp;
		pr("Ring %d: ",rp);
		int sz=0;
		for(int x=i;!rid[x];x=b[x]){
			rid[x]=rp;
			rpos[x]=++sz;
			pr("%d:%d  ",sz,x);
		}
		rs[rp].sz=sz;
		pr("\n");
	}
	Fe(x,1,n)ins(x,a[x]);
	
	F(i,0,m){
		int o=read(1,2);
		if(o==1){
			int x=read(1,n),y=read(1,n);
			del(x,a[x]);
			a[x]=y;
			ins(x,a[x]);
		}else{
			int l=read(1,n),r=read(l,n),x=read(1,n);
			que(l,r,x);
		}
	}
	Fe(x,1,n)del(x,a[x]);
	
	tr.alloc(n);
	Fe(i,1,rp){
		pr("\n\nRing %d cal:\n",i);
		rs[i].cal();
	}
	Fe(i,1,ansp)printf("%d\n",ans[i]);
	return 0;
}