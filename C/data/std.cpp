#include<bits/stdc++.h>
//#pragma gcc optimize(3)
#define gc getchar()
//char buf[100000],*buff = buf + 100000;
//#define gc ((buff == buf + 100000 ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
#define pc putchar
//char bfu[100000000],*bfuu = bfu;
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
int n,a[1010][1010];
int belx[1000010],bely[1000010];
int ans[2000010][4],k;
inline void add(int x1,int y1,int x2,int y2){
	if((x1 == x2) == (y1 == y2)) return;
	ans[++k][0] = x1;ans[k][1] = y1;ans[k][2] = x2;ans[k][3] = y2;
	swap(a[x1][y1],a[x2][y2]);
	belx[a[x1][y1]] = x1;bely[a[x1][y1]] = y1;
	belx[a[x2][y2]] = x2;bely[a[x2][y2]] = y2;
}
#define val(x,y) (((x) - 1) * n + (y)) 
#define qx(p) (((p) - 1) / n + 1)
#define qy(p) (((p) - 1) % n + 1)
inline bool chk(){
	for(int i = 1;i <= n;++i){
		for(int j = 1;j <= n;++j){
			//cerr<<a[i][j]<<" \n"[j == n];
			if(a[i][j] != val(i,j)) return 0;
		}
	}
	return 1;
}
bool vis[1010];
int b[1010],m;
int main(){
	srand(time(0));rd();
	//file("");
	int i,j,p;
	n = read();
	for(i = 1;i <= n;++i){
		for(j = 1;j <= n;++j){
			p = read();
			a[i][j] = p;belx[p] = i;bely[p] = j;
		}
	}
	
	for(i = 1;i < n;++i){
		memset(vis,0,sizeof(vis));
		//for(j = 1;j <= n;++j) cerr<<j<<":"<<val(i,j)<<" "<<bely[val(i,j)]<<"&"<<endl;
		for(j = 1,p = val(i,j);!vis[j];j = bely[p],p = val(i,j)) vis[j] = 1;
		memset(vis,0,sizeof(vis));
		p = val(i,j);b[m = 1] = p;vis[j] = 1;
		for(int k = bely[p];k != j;k = bely[p]){
			p = val(i,k);
			b[++m] = p;
			vis[k] = 1;
		} 
		//cerr<<i<<": ";
		for(j = 1;j <= m;++j){
			p = b[j];
			//cerr<<p<<" \n"[j == m];
			if(belx[p] != i) add(belx[p],bely[p],i,bely[p]);
		}
		for(j = 1;j <= m;++j){
			p = b[j];
			if(bely[p] != qy(p)) add(i,bely[p],i,qy(p));
		}
		for(j = 1;j <= n;++j) if(!vis[j]){
			p = val(i,j);
			if(bely[p] != j) add(belx[p],bely[p],belx[p],j);
			if(belx[p] != i) add(belx[p],bely[p],i,bely[p]);
		}
	}
	for(j = 1;j <= n;++j){
		p = val(n,j);
		if(bely[p] != j) add(n,bely[p],n,j);
	}
	
	if(chk()){
		print(k);pc('\n');
		cerr<<"ans: "<<2 * n * n - 2 * n<<endl;
		for(i = 1;i <= k;++i){
			//print(ans[i][0]);pc(' ');print(ans[i][1]);pc(' ');
			//print(ans[i][2]);pc(' ');print(ans[i][3]);pc('\n');
		}
	}
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}
