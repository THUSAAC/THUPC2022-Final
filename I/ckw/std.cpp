#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define ull unsigned lint
#define db long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define gc getchar()
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
inline int inn()
{
	int x,ch;while((ch=gc)<'0'||ch>'9');
	x=ch^'0';while((ch=gc)>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch^'0');return x;
}
const int N=110;int a[N][N],b[N][N],e[N][N],vis[N][N],del[N],cnt[N],c[10],n,m;
vector<pii> cv;queue<pii> q;lint ans1,ans2,ans3,ans4;
inline int gabs(int x) { return x<0?-x:x; }
inline int adjoin(int x1,int y1,int x2,int y2) { int dx=gabs(x1-x2),dy=gabs(y1-y2);return (dx==0&&dy==1)||(dx==1&&dy==0); }
inline bool erasable_x(int x,int y) { if(x<=0||x+2>n) return false;int c=a[x][y];return c&&a[x+1][y]==c&&a[x+2][y]==c; }
inline bool erasable_y(int x,int y) { if(y<=0||y+2>m) return false;int c=a[x][y];return c&&a[x][y+1]==c&&a[x][y+2]==c; }
inline bool erasable(int x,int y) { if(!a[x][y]) return false;return erasable_x(x-2,y)||erasable_x(x-1,y)||erasable_x(x,y)||erasable_y(x,y-2)||erasable_y(x,y-1)||erasable_y(x,y); }
inline void erase(int x,int y) { if(a[x][y]&&!e[x][y]) e[x][y]=1,q.push(mp(x,y)); }
inline int id(int i,int j) { return (i-1)*m+j; }
int dfs(int x,int y,int c)
{
	if(x<1||x>n||y<1||y>m||!e[x][y]||a[x][y]!=c||vis[x][y]) return 0;
	return vis[x][y]=1,dfs(x-1,y,c)+dfs(x+1,y,c)+dfs(x,y-1,c)+dfs(x,y+1,c)+1;
}
inline void eliminate()
{
	rep(i,1,n) rep(j,1,m) if(a[i][j])
	{
		if(erasable_x(i,j)) erase(i,j),erase(i+1,j),erase(i+2,j);
		if(erasable_y(i,j)) erase(i,j),erase(i,j+1),erase(i,j+2);
	}
	rep(i,1,n) rep(j,1,m) vis[i][j]=0;int sz=0;
	rep(i,1,n) rep(j,1,m) if(a[i][j]&&e[i][j]&&!vis[i][j]) sz=dfs(i,j,a[i][j]),ans3+=50ll*(sz-3)*(sz-3);
}
inline bool Eliminate(int term)
{
	while(!q.empty()) q.pop();rep(i,1,n) rep(j,1,m) e[i][j]=0;
	eliminate();if(q.empty()) return false;
	while(!q.empty())
	{
		int x=q.front().fir,y=q.front().sec;q.pop();
		int c=a[x][y],tp=b[x][y];
		if(!tp) continue;
		switch(tp)
		{
			case 1:rep(j,1,m) erase(x,j);break;
			case 2:rep(i,1,n) erase(i,y);break;
			case 3:rep(j,1,m) erase(x,j);rep(i,1,n) erase(i,y);break;
			case 4:rep(i,max(x-1,1),min(x+1,n)) rep(j,max(y-1,1),min(y+1,m)) erase(i,j);break; 
			case 5:rep(i,max(x-2,1),min(x+2,n)) rep(j,max(y-2,1),min(y+2,m)) erase(i,j);break;
			case 6:
				if(del[c]) break;del[c]=1;
				rep(i,1,n) rep(j,1,m) if(a[i][j]==c) erase(i,j);break;
			default:break;
		}
	}
	int cs=0;rep(i,1,n) rep(j,1,m) if(e[i][j]) cs+=a[i][j],a[i][j]=b[i][j]=0;
	ans1+=(lint)term*cs;return true;
}
inline void Fall() { rep(j,1,m) { int c=n;for(int i=n;i;i--) if(a[i][j]) a[c][j]=a[i][j],b[c][j]=b[i][j],c--;while(c) a[c][j]=b[c][j]=0,c--; } }
inline int _calc()
{
	int ans=0;
	rep(i,0,4) if(cnt[c[i]]==5) ans=max(ans,1000+c[i]*10);
	rep(i,0,4) if(cnt[c[i]]==4) ans=max(ans,750+c[i]*5);
	rep(i,0,4) if(cnt[c[i]]==3)
	{
		rep(j,0,4) if(cnt[c[j]]==2) ans=max(ans,500+c[i]*3+c[j]);
		ans=max(ans,300+c[i]*3);
	}
	rep(i,0,4) if(cnt[c[i]]==2)
	{
		rep(j,i+1,4) if(c[i]!=c[j]&&cnt[c[j]]==2) ans=max(ans,200+c[i]+c[j]+max(c[i],c[j]));
		ans=max(ans,100+c[i]*2);
	}
	int cx=0,c1=0;rep(i,0,4) cx=max(cx,c[i]),c1+=(cnt[c[i]]==1);
	if(c1==5) ans=max(ans,50+cx);return ans;
}
inline int calc(int i=0)
{
	if(i==5) return _calc();int ans=0;
	if(cv[i].fir) cnt[c[i]=cv[i].fir]++,ans=max(ans,calc(i+1)),cnt[cv[i].fir]--;
	if(cv[i].sec) cnt[c[i]=cv[i].sec]++,ans=max(ans,calc(i+1)),cnt[cv[i].sec]--;
	return ans;
}
inline int oper(int x1,int y1,int x2,int y2)
{
	while(!q.empty()) q.pop();int L=0;pii c=mp(0,0);
	swap(a[x1][y1],a[x2][y2]),swap(b[x1][y1],b[x2][y2]);
	if(erasable(x1,y1)) c.fir=a[x1][y1];
	if(erasable(x2,y2)) c.sec=a[x2][y2];
	if(c==mp(0,0)) return swap(a[x1][y1],a[x2][y2]),swap(b[x1][y1],b[x2][y2]),0;
	while(Eliminate(L+1)) Fall(),L++;
	ans2+=80ll*(L-1)*(L-1),cv.pb(c);
	if((int)cv.size()==5) ans4+=calc(),cv.clear();
	return 1;
}
int main()
{
	n=inn(),m=inn(),inn();int q=inn(),fail=0;
	rep(i,1,n) rep(j,1,m) a[i][j]=inn();
	rep(i,1,n) rep(j,1,m) b[i][j]=inn();
	rep(i,1,q)
	{
		int x1=inn(),y1=inn(),x2=inn(),y2=inn(),c1=a[x1][y1],c2=a[x2][y2];
		if(!adjoin(x1,y1,x2,y2)||!c1||!c2||c1==c2) { fail++;continue; }
		fail+=!oper(x1,y1,x2,y2);
	}
	lint ans=ans1+ans2+ans3+ans4;
	if(!fail) ans+=1000;fail=0;
	rep(i,1,n) rep(j,1,m) if(a[i][j]) fail=1;
	if(!fail) ans+=10000;
	return !printf("%lld\n",ans);
}
