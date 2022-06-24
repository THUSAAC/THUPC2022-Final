#include<bits/stdc++.h>
#define gc getchar()
#define pc putchar
#define li long long
using namespace std;
inline li read(li l = 0,li r = 1e9){
	li x = 0;
	int c = gc;
	while(c < '0' || c > '9') assert(c == ' ' || c == '\n' || c == '\r'),c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	assert(c == -1 || c == ' ' || c == '\n' || c == '\r');
	assert(x >= l && x <= r);
	return x;
}
int end_chk(){
	char c;
	do{
		c = gc;
		assert(c == -1 || c == ' ' || c == '\n' || c == '\r');			
	}while(c != -1);
	return 0;
}
int n,m,s;
bool vis[1000010];
li a[110];
struct edge{
	int to,nxt,val;
}e[10010];
int cnt,fir[110];
int ru[110];
void ins(int u,int v,int w){
	e[++cnt].to = v;e[cnt].nxt = fir[u];fir[u] = cnt;e[cnt].val = w;
	++ru[v];
}
int q[110],h,t;
int main(){
	n = read(2,100);
	m = read(1,n * (n - 1) / 2);
	s = read(1,n);
	a[0] = 1;
	int i,u,v,w;
	for(i = 1;i < n;++i) a[i] = read(a[i - 1]); 
	for(i = 1;i <= m;++i){
		u = read(1,n);v = read(1,n);w = read(1,1e9);
		ins(u,v,w);
	}
	for(i = 1;i <= n;++i) if(!ru[i]) q[++t] = i;
	while(h < t){
		u = q[++h];
		for(i = fir[u];i;i = e[i].nxt){
			--ru[e[i].to];
			if(!ru[e[i].to]) q[++t] = e[i].to;
		}
	}
	assert(t == n);
	return end_chk();
}
