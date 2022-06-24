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
int f[52][52][52][52];
int bel[4][14];
inline int js(int l,int r){
	if(l == 8) return 49;
	return (7 - l) * 7 + r - 7;
}
int dfs(int l0,int r0,int l1,int r1,int l2,int r2,int l3,int r3,bool fg){
	if(l0 == 1 && r0 == 13 && l1 == 1 && r1 == 13 && l2 == 1 && r2 == 13 && l3 == 1 && r3 == 13) 
		return 1;
	int q0 = js(l0,r0),q1 = js(l1,r1),q2 = js(l2,r2),q3 = js(l3,r3);
	if(~f[q0][q1][q2][q3]) return f[q0][q1][q2][q3];
	int pl0 = l0 - 1,pr0 = r0 + 1;
	int pl1 = l1 - 1,pr1 = r1 + 1;
	int pl2 = l2 - 1,pr2 = r2 + 1;
	int pl3 = l3 - 1,pr3 = r3 + 1;
	f[q0][q1][q2][q3] = 0;
	if(pl0 && bel[0][pl0] == fg) 
		f[q0][q1][q2][q3] = max(f[q0][q1][q2][q3],2 - dfs(pl0,r0,l1,r1,l2,r2,l3,r3,!fg));
	if(pr0 != 14 && l0 != 8 && bel[0][pr0] == fg) 
		f[q0][q1][q2][q3] = max(f[q0][q1][q2][q3],2 - dfs(l0,pr0,l1,r1,l2,r2,l3,r3,!fg));
	
	if(pl1 && bel[1][pl1] == fg) 
		f[q0][q1][q2][q3] = max(f[q0][q1][q2][q3],2 - dfs(l0,r0,pl1,r1,l2,r2,l3,r3,!fg));
	if(pr1 != 14 && l1 != 8 && bel[1][pr1] == fg) 
		f[q0][q1][q2][q3] = max(f[q0][q1][q2][q3],2 - dfs(l0,r0,l1,pr1,l2,r2,l3,r3,!fg));
	
	if(pl2 && bel[2][pl2] == fg) 
		f[q0][q1][q2][q3] = max(f[q0][q1][q2][q3],2 - dfs(l0,r0,l1,r1,pl2,r2,l3,r3,!fg));
	if(pr2 != 14 && l2 != 8 && bel[2][pr2] == fg) 
		f[q0][q1][q2][q3] = max(f[q0][q1][q2][q3],2 - dfs(l0,r0,l1,r1,l2,pr2,l3,r3,!fg));
	
	if(pl3 && bel[3][pl3] == fg) 
		f[q0][q1][q2][q3] = max(f[q0][q1][q2][q3],2 - dfs(l0,r0,l1,r1,l2,r2,pl3,r3,!fg));
	if(pr3 != 14 && l3 != 8 && bel[3][pr3] == fg) 
		f[q0][q1][q2][q3] = max(f[q0][q1][q2][q3],2 - dfs(l0,r0,l1,r1,l2,r2,l3,pr3,!fg));
	
	//cerr<<l0<<" "<<r0<<" "<<l1<<" "<<r1<<" "<<l2<<" "<<r2<<" "<<l3<<" "<<r3<<": "<<q0<<" "<<q1<<" "<<q2<<" "<<q3<<"   "<<f[q0][q1][q2][q3]<<endl;
	return f[q0][q1][q2][q3];
}
bool vis[4][14];
int main(){
	srand(time(0));rd();
	//file("");
	int i,j,x,y;
	for(i = 0;i < 4;++i) for(j = 1;j <= 13;++j) bel[i][j] = 1;
	for(i = 1;i <= 26;++i){
		char c[5];
		scanf("%s",c);
		if(c[0] == 'C') x = 0;
		else if(c[0] == 'D') x = 1;
		else if(c[0] == 'H') x = 2;
		else x = 3;
		if(c[2] == '\0') y = c[1] - '0';
		else y = (c[1] - '0') * 10 + c[2] - '0';
		//cerr<<x<<" "<<y<<endl;
		bel[x][y] = 0; 
	}
	//for(i = 0;i < 4;++i) for(j = 1;j <= 13;++j) cerr<<bel[i][j]<<" ";cerr<<endl;
	//return 0;
	int fg = 0;
	if(bel[3][7] == 1){
		for(i = 0;i < 4;++i) for(j = 1;j <= 13;++j) bel[i][j] ^= 1;
		fg = 2;
	}
	memset(f,-1,sizeof(f));
	f[49][49][49][0] = dfs(8,7,8,7,8,7,7,7,1);
	//cerr<<f[49][49][49][0]<<" "<<fg<<endl;
	if(f[49][49][49][0] == 1) puts("Draw");
	else puts((f[49][49][49][0] ^ fg) ? "Bob" : "Alice");
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}


