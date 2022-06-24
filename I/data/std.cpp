#include<bits/stdc++.h>
#define gc getchar()
#define fi first
#define se second
//#define TEST 
using namespace std;
inline int read(){
	#ifdef TEST
	int a;cin>>a;return a;
	#endif
	int x = 0,c = gc;
	while(c < '0' || c > '9') c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return x;
}
#define li long long
#define pc putchar
inline void prt(li x){
	if(x >= 10) prt(x / 10);
	pc(x % 10 + '0');
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	prt(x);
}
int n,m,k,q,nw;
struct node{
	int a,b;
	inline node(int _a = 0,int _b = 0){a = _a;b = _b;}
}a[110][110];
int ht[110]; 
int ans,stp,_dpt;
struct pai{
	int a[6],b[6];
}p;
bool chk_xiao(int,int);
int vis[110][110],vis2[110][110];
int cnt = 0;
int qu[10010][2],h,t;
int dx[4] = {-1,0,1,0},dy[4] = {0,1,0,-1}; 
void out(bool cls = 0,bool inp = 0){
	#ifdef TEST
	if(cls) system("cls");
	cerr<<"score: "<<ans<<endl;
	cerr<<"step: "<<stp<<endl;
	cerr<<"dpt: "<<_dpt<<endl;
	cerr<<"nw: "<<nw<<endl;
	cerr<<"col: ";
	for(int i = 0;i <= nw;++i) cerr<<"("<<p.a[i]<<", "<<p.b[i]<<")  ";
	cerr<<endl<<endl;
	for(int i = 1;i <= n;++i){
		for(int j = 1;j <= m;++j){
			int t1 = (vis[i][j] != cnt);
			cerr<<"("<<a[i][j].a * t1<<", "<<a[i][j].b * t1<<")  ";
		}
		cerr<<endl;
	}
	if(inp){
		cerr<<"please input: "<<endl;
	}
	else{
		cerr<<"**************************************"<<endl;
		system("pause");
	}
	#endif
}
inline bool chk_can_xiao(int x,int y){//基本消除条件 
	if(!a[x][y].a) return 0;
	int px = 0,py = 0,o = a[x][y].a;
	if(x && a[x - 1][y].a == o){
		++px;
		if(x > 1 && a[x - 2][y].a == o) return 1;
	}
	if(x != n && a[x + 1][y].a == o){
		++px;
		if(x < n - 1 && a[x + 2][y].a == o) return 1;
	}
	if(px >= 2) return 1;
	if(y && a[x][y - 1].a == o){
		++py;
		if(y > 1 && a[x][y - 2].a == o) return 1;
	}
	if(y != m && a[x][y + 1].a == o){
		++py;
		if(y < m - 1 && a[x][y + 2].a == o) return 1;
	}
	return py >= 2;
}
void down(){
	for(int j = 1;j <= m;++j){
		int o = n + 1;
		for(int i = n;i > n - ht[j];--i) if(a[i][j].a && vis[i][j] != cnt){
			a[--o][j] = a[i][j];
		}
		for(int i = o - 1;i > n - ht[j];--i) a[i][j] = node(0,0);
		ht[j] = n - o + 1;
	}
}
int dfs_zuhe(int x,int y){
	vis2[x][y] = cnt;
	int sl = 1;
	for(int i = 0;i < 3;++i){
		int tx = x + dx[i],ty = y + dy[i];
		if(tx >= 1 && tx <= n && ty >= 1 && ty <= m){
			if(vis[tx][ty] == cnt && a[tx][ty].a == a[x][y].a && vis2[tx][ty] != cnt){
				sl += dfs_zuhe(tx,ty);
			}
		}
	}
	return sl;
} 
inline void addq(int x,int y,int col = 0){
	if(x >= 1 && x <= n && y >= 1 && y <= m && a[x][y].a && vis[x][y] != cnt){
		if(!col || col == a[x][y].a){
			//cerr<<"***"<<x<<" "<<y<<" "<<col<<" "<<a[x][y].a<<endl; 
			vis[x][y] = cnt;
			qu[++t][0] = x;qu[t][1] = y;
		}
	}
}
void teshu(){
	int i,j;
	while(h < t){
		int tx = qu[++h][0],ty = qu[h][1];
		//cerr<<tx<<" "<<ty<<":::"<<endl;
		int col = a[tx][ty].a,op = a[tx][ty].b;
		if(op == 0) continue;//无效果
		if(op == 1 || op == 3){//同一行 
			for(j = 1;j <= m;++j) addq(tx,j);
		} 
		if(op == 2 || op == 3){//同一列 
			for(i = 1;i <= n;++i) addq(i,ty);
		}
		if(op == 4 || op == 5){//正方形 
			int r = 1 + (op == 5);
			for(i = tx - r;i <= tx + r;++i){
				for(j = ty - r;j <= ty + r;++j){
					addq(i,j);
				}
			}
		}
		if(op == 6){//同颜色 
			for(int j = 1;j <= m;++j){
				for(int i = n;i > n - ht[j];--i){
					addq(i,j,col);
				}
			} 
		}
	}
}
bool chk_xiao(int dpt,int idx){
	_dpt = dpt; 
	int i,j;
	bool fg = 0;
	h = t = 0;
	++cnt;
	if(dpt == 1) p.a[idx] = p.b[idx] = 0;
	out(1,0);
	for(j = 1;j <= m;++j){
		for(i = n;i > n - ht[j];--i) if(chk_can_xiao(i,j)){
			fg = 1;
			vis[i][j] = cnt;
			if(dpt == 1){//记录主颜色 
				if(!p.a[idx]) p.a[idx] = a[i][j].a;
				else if(p.a[idx] != a[i][j].a) p.b[idx] = a[i][j].a;
			}
			qu[++t][0] = i;qu[t][1] = j;
		}
	}
	if(!fg) return 0;
	for(i = 1;i <= t;++i){
		int tx = qu[i][0],ty = qu[i][1];
		//cerr<<tx<<" "<<ty<<"&"<<endl;
		if(vis2[tx][ty] == cnt) continue;
		int tmp = dfs_zuhe(tx,ty);
		ans += 50 * (tmp - 3) * (tmp - 3);//组合奖分 
	}
	teshu();//触发特殊效果 
	for(i = 1;i <= t;++i) ans += a[qu[i][0]][qu[i][1]].a * dpt;//消除奖分 
	if(dpt > 1) ans += 80 * (dpt * 2 - 3);//连消奖分 
	out(0,0);
	down();//下落 
	++cnt;
	out(0,0);
	chk_xiao(dpt + 1,idx);
	return 1;
}
#define e(x,y) (t[x] == t[y])
int chk_paii(){
	int t[6];
	memcpy(t,p.a,sizeof(t));
	sort(t,t + 5);
	//五条 
	if(e(0,1) && e(1,2) && e(2,3) && e(3,4))
		return 1000 + t[0] * 10;
	//四条
	if(e(1,2) && e(2,3) && (e(0,1) || e(3,4)))
		return 750 + t[2] * 5;
	//葫芦
	if(e(0,1) && e(3,4)){
		if(e(1,2)) return 500 + t[2] * 3 + t[4];
		if(e(2,3)) return 500 + t[2] * 3 + t[0];
	}
	//三条
	if(e(0,1) && e(1,2)) return 300 + t[2] * 3;
	if(e(1,2) && e(2,3)) return 300 + t[2] * 3;
	if(e(2,3) && e(3,4)) return 300 + t[2] * 3;
	//两对
	if(e(0,1) && e(2,3)) return 200 + t[3] * 2 + t[1];
	if(e(0,1) && e(3,4)) return 200 + t[3] * 2 + t[1];
	if(e(1,2) && e(3,4)) return 200 + t[3] * 2 + t[1];
	//一对
	if(e(0,1)) return 100 + t[0] * 2;
	if(e(1,2)) return 100 + t[1] * 2;
	if(e(2,3)) return 100 + t[2] * 2;
	if(e(3,4)) return 100 + t[3] * 2;
	//高牌
	return 50 + t[4]; 
}
int chk_pai(int dpt){
	if(dpt == 5){
		int o = chk_paii();
		//for(int i = 0;i < 5;++i) cerr<<p.a[i]<<" ";cerr<<": "<<o<<endl;
		#ifdef TEST
		for(int i = 0;i < 5;++i) cerr<<p.a[i]<<" ";cerr<<": "<<o<<endl;
		#endif
		return o;
	} 
	int as = chk_pai(dpt + 1);
	if(p.b[dpt]){
		swap(p.a[dpt],p.b[dpt]);
		as = max(as,chk_pai(dpt + 1));
	}
	//if(dpt == 0) cerr<<as<<endl<<endl;
	return as;
}
inline bool chk_all(){
	for(int i = 1;i <= m;++i) if(ht[i]) return 0;
	return 1;
}
long long s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline long long rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int main(){
	//srand(time(0));
	srand(233333667);
	rd();
	int i,j;
	int xa,xb,ya,yb;
	bool suc = 1;
	#ifdef TEST
	int tsd = read();
	char ch[50];
	sprintf(ch,"%d.in",tsd);
	freopen(ch,"w",stdout);
	#endif
	n = read();m = read();k = read();q = read();
	#ifdef TEST
	print(n);pc(' ');print(m);pc(' ');print(k);pc(' ');print(q);pc('\n');
	#endif
	for(i = 1;i <= m;++i) ht[i] = n;
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j){
			#ifdef TEST
			do{
				a[i][j].a = rd() % k + 1;
			}while(chk_can_xiao(i,j));
			print(a[i][j].a);pc(j == m ? '\n' : ' ');
			#else 
			a[i][j].a = read();
			#endif
		} 
	}
	for(i = 1;i <= n;++i){
		for(j = 1;j <= m;++j){
			#ifdef TEST
			a[i][j].b = rd() % 20 ? 0 : rd() % 7;
			print(a[i][j].b);pc(j == m ? '\n' : ' ');
			#else 
			a[i][j].b = read();
			#endif
		} 
	}
	for(i = 0;i < q;++i){
		stp = i + 1;++cnt;
		out(1,1);
		//cerr<<ans<<endl;
		xa = read();ya = read();xb = read();yb = read();
		#ifdef TEST
		print(xa);pc(' ');print(ya);pc(' ');print(xb);pc(' ');print(yb);pc('\n');
		#endif
		if(abs(xa - xb) + abs(ya - yb) != 1 || !a[xa][ya].a || !a[xb][yb].a){
			suc = 0;
			continue;
		}
		swap(a[xa][ya],a[xb][yb]);
		if(!chk_xiao(1,nw)){
			swap(a[xa][ya],a[xb][yb]);
			suc = 0;
			continue;
		}
		if(++nw == 5){
			ans += chk_pai(0);//牌型奖分 
			nw = 0;
		} 
	}
	if(suc) ans += 1000;//终局奖分1 
	if(chk_all()) ans += 10000;//终局奖分2 
	cout<<ans<<endl;
	return 0;
}
