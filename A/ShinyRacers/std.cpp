#include <cstdio>
using namespace std;
#define cmin(_a, _b) (_a > (_b) ? _a = _b : 0)
int id[16][16], f[54][54][54][54], vis[54][54][54][54];
int card[4][16], suitid[127];
char s[9];
int dfs(int p, int sl, int sr, int hl, int hr, int cl, int cr, int dl, int dr){
	int sid = id[sl][sr], hid = id[hl][hr], cid = id[cl][cr], did = id[dl][dr];
	if (vis[sid][hid][cid][did]) return f[sid][hid][cid][did];
	vis[sid][hid][cid][did] = 1;
	int ans = 42, tmp;
	if (sl > 1 && card[0][sl - 1] == p) {
		tmp = dfs(p ^ 1, sl - 1, sr, hl, hr, cl, cr, dl, dr);
		cmin(ans, tmp);
	}
	if (sr < 13 && card[0][sr + 1] == p) {
		tmp = dfs(p ^ 1, sl, sr + 1, hl, hr, cl, cr, dl, dr);
		cmin(ans, tmp);
	}
	if (hl > hr) {
		if (card[1][7] == p) {
			tmp = dfs(p ^ 1, sl, sr, 7, 7, cl, cr, dl, dr);
			cmin(ans, tmp);
		}
	}
	else {
		if (hl > 1 && card[1][hl - 1] == p) {
			tmp = dfs(p ^ 1, sl, sr, hl - 1, hr, cl, cr, dl, dr);
			cmin(ans, tmp);
		}
		if (hr < 13 && card[1][hr + 1] == p) {
			tmp = dfs(p ^ 1, sl, sr, hl, hr + 1, cl, cr, dl, dr);
			cmin(ans, tmp);
		}
	}
	if (cl > cr) {
		if (card[2][7] == p) {
			tmp = dfs(p ^ 1, sl, sr, hl, hr, 7, 7, dl, dr);
			cmin(ans, tmp);
		}
	}
	else {
		if (cl > 1 && card[2][cl - 1] == p) {
			tmp = dfs(p ^ 1, sl, sr, hl, hr, cl - 1, cr, dl, dr);
			cmin(ans, tmp);
		}
		if (cr < 13 && card[2][cr + 1] == p) {
			tmp = dfs(p ^ 1, sl, sr, hl, hr, cl, cr + 1, dl, dr);
			cmin(ans, tmp);
		}
	}
	if (dl > dr) {
		if (card[3][7] == p) {
			tmp = dfs(p ^ 1, sl, sr, hl, hr, cl, cr, 7, 7);
			cmin(ans, tmp);
		}
	}
	else {
		if (dl > 1 && card[3][dl - 1] == p) {
			tmp = dfs(p ^ 1, sl, sr, hl, hr, cl, cr, dl - 1, dr);
			cmin(ans, tmp);
		}
		if (dr < 13 && card[3][dr + 1] == p) {
			tmp = dfs(p ^ 1, sl, sr, hl, hr, cl, cr, dl, dr + 1);
			cmin(ans, tmp);
		}
	}
	if (ans == 42) {
		return f[sid][hid][cid][did] = -1;
	}
	return f[sid][hid][cid][did] = -ans;
}
int main(){
	int i, j, tot = 0, suit, point, ans;
	for (i = 7; i > 0; --i) {
		for (j = 7; j <= 13; ++j) {
			id[i][j] = ++tot;
		}
	}
	id[8][6] = ++tot;
	suitid['S'] = 0;
	suitid['H'] = 1;
	suitid['C'] = 2;
	suitid['D'] = 3;
	
	for (i = 0; i < 26; ++i) {
		scanf("%s", s);
		suit = suitid[s[0]];
		sscanf(s + 1, "%d", &point);
		card[suit][point] = 1;
	}
	
	vis[id[1][13]][id[1][13]][id[1][13]][id[1][13]] = 1;
	f[id[1][13]][id[1][13]][id[1][13]][id[1][13]] = 0;
	ans = dfs(card[0][7] ^ 1, 7, 7, 8, 6, 8, 6, 8, 6);
	if (ans == 0) {
		puts("Draw");
	}
	else if (ans == 1) {
		puts(card[0][7] ? "Bob" : "Alice");
	}
	else {
		puts(card[0][7] ? "Alice" : "Bob");
	}
	return 0;
}