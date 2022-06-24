#include<bits/stdc++.h>
//#pragma gcc optimize(3)
#define gc getchar()
//char buf[100000],*buff = buf + 100000;
//#define gc ((buff == buf + 100000 ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
#define pc putchar
//char bfu[10000000],*bfuu = bfu;
//#define pc(x) (*(bfuu++) = x)
#define li long long
#define uli unsigned li
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define md int mid = l + r >> 1
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
using namespace std;
//const int mo = 998244353;
//const int mo = 1000000007;
inline li read(){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9') y = c,c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return y == '-' ? -x : x;
}
inline void prt(li x){
	if(x >= 10) prt(x / 10);
	pc(x % 10 + '0');
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	prt(x);
}
inline void file(char *s){
	char c[50];
	sprintf(c,"%s.in",s);
	freopen(c,"r",stdin);
	sprintf(c,"%s.out",s);
	freopen(c,"w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int n,m,s,g;
struct edge{
	int to,nxt,val;
}e[10010];
int cnt,fir[110];
int ru[110];
void ins(int u,int v,int w){
	e[++cnt].to = v;e[cnt].nxt = fir[u];fir[u] = cnt;e[cnt].val = w;
	++ru[v];
}
li f[110][110][110];
int q[110],h,t;
li a[110]; 
inline li gcd(li q,li w){
	return !w ? q : gcd(w,q % w);
}
int main(){
	srand(time(0));rd();
	//file("");
	int i,j,l,o,u,v,w,x;
	n = read();m = read();s = read();
	for(i = 1;i < n;++i) a[i] = read();
	memset(f,0xfe,sizeof(f));
	for(i = 1;i <= m;++i){
		u = read();v = read();w = read();
		ins(u,v,w);
	}
	for(i = 1;i <= n;++i) if(!ru[i]) q[++t] = i;
	int st = 0;
	while(h < t){
		u = q[++h];
		if(u == s) st = h;
		for(i = fir[u];i;i = e[i].nxt){
			--ru[e[i].to];
			if(!ru[e[i].to]) q[++t] = e[i].to;
		}
	}
	for(i = st;i < n;++i){
		u = q[i];
		if(i == st) f[u][0][0] = 0;
		for(j = 0;j <= i - st;++j){
			for(l = 0;l <= j;++l) if(f[u][j][l] >= 0){
				for(o = fir[u];o;o = e[o].nxt){
					v = e[o].to;
					w = e[o].val;
					if(j != 0){//继续在第j层走 
						x = (l + w) % (j + 1);
						f[v][j][x] = max(f[v][j][x],f[u][j][l] + a[j]);
					}
					if(l == 0){//走到第j+1层 
						x = w % (j + 2);
						f[v][j + 1][x] = max(f[v][j + 1][x],f[u][j][l] + a[j + 1]);
					}
				}
			}
		}
	}
	li ans = -1,k = 1;
	for(j = st + 1;j <= n;++j){
		g = q[j];
		for(i = 1;i < n;++i){
			if(f[g][i][0] >= 0){
				if(f[g][i][0] * k > ans * i){
					ans = f[g][i][0];
					k = i;
				}
			}
		}
	}
	if(ans == -1) k = -1;
	else{
		li d = gcd(ans,k);
		ans /= d;k /= d;
	}
	print(ans);pc(' ');print(k);pc('\n');
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}
