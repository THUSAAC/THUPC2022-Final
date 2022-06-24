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
	if(x < l || x > r) cerr<<l<<" "<<r<<":"<<x<<endl;
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
int n,m,k,q;
int main(){
	n = read(1,50);m = read(1,50);k = read(1,100);q = read(1,1000);
	int i,j;
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j) read(1,k);
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j) read(0,6);
	//return 0;
	for(i = 1;i <= q;++i){
		read(1,n);read(1,m);read(1,n);read(1,m);
	}
	return end_chk();
}
