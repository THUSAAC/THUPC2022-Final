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
inline void file(int d){
	char c[50];
	sprintf(c,"%d.in",d);
	//freopen(c,"r",stdin);
	//sprintf(c,"%d.out",d);
	freopen(c,"w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int tsd,n,m,k,q;
int a[52][52],b[52][52];
inline bool chk_can_xiao(int x,int y){//基本消除条件 
	if(!a[x][y]) return 0;
	int px = 0,py = 0,o = a[x][y];
	if(x && a[x - 1][y] == o){
		++px;
		if(x > 1 && a[x - 2][y] == o) return 1;
	}
	if(x != n && a[x + 1][y] == o){
		++px;
		if(x < n - 1 && a[x + 2][y] == o) return 1;
	}
	if(px >= 2) return 1;
	if(y && a[x][y - 1] == o){
		++py;
		if(y > 1 && a[x][y - 2] == o) return 1;
	}
	if(y != m && a[x][y + 1] == o){
		++py;
		if(y < m - 1 && a[x][y + 2] == o) return 1;
	}
	return py >= 2;
}
void wk12(){
	tsd = 12;
	n = 49;
	m = 50;
	q = 1;
	k = 65;
	file(tsd);
	print(n);pc(' ');print(m);pc(' ');print(k);pc(' ');print(q);pc('\n');
	a[1][1] = 1;
	int i,j;
	for(i = 2;i <= 17;++i) a[i][1] = i - 1;
	a[18][1] = 16;a[19][1] = 15;a[20][1] = 16;a[21][1] = 15;
	for(i = 22;i <= 49;++i) a[i][1] = (51 - i) / 2;
	for(j = 2;j <= m;++j){
		for(i = 1;i <= 16;++i) a[i][j] = i + j - 1;
		a[17][j] = 15 + j;a[18][j] = j - 1;a[19][j] = 15 + j;
		for(i = 20;i <= 49;++i) a[i][j] = (49 - i) / 2 + j;
	}
	for(j = 1;j <= m;++j) b[1][j] = 6;
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(a[i][j]),pc(j == m ? '\n' : ' ');
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(b[i][j]),pc(j == m ? '\n' : ' ');
	}
	puts("19 1 20 1");
}
void wk13(){
	tsd = 13;
	n = 50;
	m = 50;
	q = 1;
	k = 100;
	file(tsd);
	print(n);pc(' ');print(m);pc(' ');print(k);pc(' ');print(q);pc('\n');
	int i,j;
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j) a[i][j] = rd() % k + 1;
	for(i = 1;i <= n;++i) b[i][i] = b[i][n - i + 1] = 4;
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(a[i][j]),pc(j == m ? '\n' : ' ');
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(b[i][j]),pc(j == m ? '\n' : ' ');
	}
	puts("1 3 1 4");
}
void wk15(){
	tsd = 15;
	n = 50;
	m = 50;
	q = 1;
	k = 9;
	file(tsd);
	print(n);pc(' ');print(m);pc(' ');print(k);pc(' ');print(q);pc('\n');
	int i,j;
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j){
		do{
			a[i][j] = rd() % k + 1;
		}while(chk_can_xiao(i,j));
	} 
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j){
		if(rd() % 50 == 0) b[i][j] = rd() % 6;
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(a[i][j]),pc(j == m ? '\n' : ' ');
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(b[i][j]),pc(j == m ? '\n' : ' ');
	}
	puts("1 3 1 4");
}
void wk16(){
	tsd = 16;
	n = 50;
	m = 50;
	q = 1;
	k = 9;
	file(tsd);
	print(n);pc(' ');print(m);pc(' ');print(k);pc(' ');print(q);pc('\n');
	int i,j;
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j){
		do{
			a[i][j] = rd() % k + 1;
		}while(chk_can_xiao(i,j));
	} 
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j){
		if(i == j) b[i][j] = rd() % 2 ? 4 : 5;
		else if(rd() % 50 == 0) b[i][j] = rd() % 6;
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(a[i][j]),pc(j == m ? '\n' : ' ');
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(b[i][j]),pc(j == m ? '\n' : ' ');
	}
	puts("1 3 1 4");
}
void sj(int x,int y){
	do{
		a[x][y] = rd() % k + 1;
	}while(chk_can_xiao(x,y));
}
void wk17(){
	tsd = 17;
	n = 50;
	m = 48;
	q = 1000;
	k = 100;
	file(tsd);
	print(n);pc(' ');print(m);pc(' ');print(k);pc(' ');print(q);pc('\n');
	int i,j;
	k = 94;
	for(j = 1;j <= m;j += 3){
		for(i = 1;i <= n;i += 2){
			int o = rd() % 6 + 95;
			if(j / 3 + i / 2 & 1){
				a[i][j] = a[i + 1][j + 1] = a[i][j + 2] = o;
				sj(i + 1,j);sj(i,j + 1);sj(i + 1,j + 2);
			}
			else{
				a[i + 1][j] = a[i][j + 1] = a[i + 1][j + 2] = o;
				sj(i,j);sj(i + 1,j + 1);sj(i,j + 2);
			}
		}
	}
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j){
		b[i][j] = 0;
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(a[i][j]),pc(j == m ? '\n' : ' ');
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(b[i][j]),pc(j == m ? '\n' : ' ');
	}
	for(i = 1;i <= q;++i){
		int tx = rd() % (n - 1) + 1,ty = rd() % (m / 3) + 1;
		print(tx);pc(' ');print(ty * 3 - 1);pc(' ');
		print(tx + 1);pc(' ');print(ty * 3 - 1);pc('\n');
	}
}
void wk18(){
	tsd = 18;
	n = 50;
	m = 48;
	q = 1000;
	k = 100;
	file(tsd);
	print(n);pc(' ');print(m);pc(' ');print(k);pc(' ');print(q);pc('\n');
	int i,j;
	k = 95;
	for(j = 1;j <= m;j += 3){
		for(i = 1;i <= n;i += 2){
			int o = rd() % 5 + 96;
			if(j / 3 + i / 2 & 1){
				a[i][j] = a[i + 1][j + 1] = a[i][j + 2] = o;
				sj(i + 1,j);sj(i,j + 1);sj(i + 1,j + 2);
			}
			else{
				a[i + 1][j] = a[i][j + 1] = a[i + 1][j + 2] = o;
				sj(i,j);sj(i + 1,j + 1);sj(i,j + 2);
			}
		}
	}
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j){
		b[i][j] = 0;
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(a[i][j]),pc(j == m ? '\n' : ' ');
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(b[i][j]),pc(j == m ? '\n' : ' ');
	}
	for(i = 1;i <= q;++i){
		int tx = rd() % (n - 1) + 1,ty = rd() % (m / 3) + 1;
		print(tx);pc(' ');print(ty * 3 - 1);pc(' ');
		print(tx + 1);pc(' ');print(ty * 3 - 1);pc('\n');
	}
}
void wk19(){
	tsd = 19;
	n = 50;
	m = 48;
	q = 300;
	k = 22;
	file(tsd);
	print(n);pc(' ');print(m);pc(' ');print(k);pc(' ');print(q);pc('\n');
	int i,j;
	for(j = 1;j <= m;j += 4){
		for(i = 1;i <= n;i += 2){
			int o1,o2;
			do{
				o1 = rd() % (k - 2) + 1;
				o2 = rd() % (k - 2) + 1;
			}while(o1 == o2);
			a[i][j] = a[i + 1][j + 1] = a[i][j + 2] = o1;
			a[i + 1][j] = a[i][j + 1] = a[i + 1][j + 2] = o2;
			a[i][j + 3] = k - 1;
			a[i + 1][j + 3] = k;
		}
	}
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j){
		b[i][j] = 0;
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(a[i][j]),pc(j == m ? '\n' : ' ');
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(b[i][j]),pc(j == m ? '\n' : ' ');
	}
	int tmp[17];memset(tmp,0,sizeof(tmp));
	for(i = 1;i <= q;++i){
		int tx,ty;
		do{
			ty = rd() % (m / 4) + 1;
		}while(tmp[ty] == 25);
		tx = ++tmp[ty];
		print(tx * 2 - 1);pc(' ');print(ty * 4 - 2);pc(' ');
		print(tx * 2);pc(' ');print(ty * 4 - 2);pc('\n');
	}
}
void wk20(){
	tsd = 20;
	n = 50;
	m = 48;
	q = 300;
	k = 8;
	file(tsd);
	print(n);pc(' ');print(m);pc(' ');print(k);pc(' ');print(q);pc('\n');
	int i,j;
	for(j = 1;j <= m;j += 4){
		for(i = 1;i <= n;i += 2){
			int o1,o2;
			do{
				o1 = rd() % (k - 2) + 1;
				o2 = rd() % (k - 2) + 1;
			}while(o1 == o2);
			a[i][j] = a[i + 1][j + 1] = a[i][j + 2] = o1;
			a[i + 1][j] = a[i][j + 1] = a[i + 1][j + 2] = o2;
			a[i][j + 3] = k - 1;
			a[i + 1][j + 3] = k;
		}
	}
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j){
		b[i][j] = 0;
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(a[i][j]),pc(j == m ? '\n' : ' ');
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(b[i][j]),pc(j == m ? '\n' : ' ');
	}
	int tmp[17];memset(tmp,0,sizeof(tmp));
	for(i = 1;i <= q;++i){
		int tx,ty;
		do{
			ty = rd() % (m / 4) + 1;
		}while(tmp[ty] == 25);
		tx = ++tmp[ty];
		print(tx * 2 - 1);pc(' ');print(ty * 4 - 2);pc(' ');
		print(tx * 2);pc(' ');print(ty * 4 - 2);pc('\n');
	}
}
void wk(int tmp,int _k){
	tsd = tmp;
	n = 50;
	m = 50;
	q = 1000;
	k = _k;
	file(tsd);
	print(n);pc(' ');print(m);pc(' ');print(k);pc(' ');print(q);pc('\n');
	int i,j;
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j){
			do{
				a[i][j] = rd() % k + 1;
			}while(chk_can_xiao(i,j));
		}
	}
	for(i = 1;i <= n;++i) for(j = 1;j <= m;++j){
		if(rd() % 100 == 0) b[i][j] = rd() % 7;
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(a[i][j]),pc(j == m ? '\n' : ' ');
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j) print(b[i][j]),pc(j == m ? '\n' : ' ');
	}
	for(i = 1;i <= q;++i){
		int tx = rd() % n + 1,ty = rd() % m + 1;
		int dx = tx,dy = ty;
		if(rd() & 1){
			if(tx == n) --dx;
			else ++dx;
		}
		else{
			if(ty == n) --dy;
			else ++dy;
		}
		print(dx);pc(' ');print(dy);pc(' ');print(tx);pc(' ');print(ty);pc('\n');
	}
}
int main(){
	srand(time(0));rd();
	int tmp = read(),k = read();
	wk(tmp,k);
	
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}


