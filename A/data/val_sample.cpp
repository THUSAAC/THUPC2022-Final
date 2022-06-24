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
int n,m;
bool vis[4][14]; 
inline void file(int d){
	char c[50];
	sprintf(c,"%d.in",d);
	freopen(c,"r",stdin);
}
int main(){
	int d;cin>>d;
	file(d);
	for(int i = 1;i <= 26;++i){
		cerr<<i<<":::"<<endl; 
		char c = gc;
		assert(c == 'C' || c == 'D' || c == 'H' || c == 'S');
		int x = c == 'C' ? 0 : c == 'D' ? 1 : c == 'H' ? 2 : 3;
		int y = read(1,13);
		assert(!vis[x][y]);
		vis[x][y] = 1;
		cerr<<x<<" "<<y<<endl;
	}
	return end_chk();
}
