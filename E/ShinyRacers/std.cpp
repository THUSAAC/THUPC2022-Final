#include <cstdio>
using namespace std;
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
long long f[108][108][108];
int head[108], deg[108], marken[108], a[108];
struct Edge {
	int to, w, next;
} e[5004];
long long gcd(long long x, long long y){
	long long z;
	while (z = x % y) {
		x = y;
		y = z;
	}
	return y;
}
int main(){
	int n, m, i, j, k, s, t, u, v, w, count = 0, ansd = 1;
	long long ansn = 0, tmp;
	scanf("%d %d %d", &n, &m, &s);
	marken[s] = 1;
	for (i = 1; i < n; ++i) scanf("%d", &a[i]);
	for (i = 1; i <= m; ++i) {
		scanf("%d %d %d", &u, &v, &w);
		e[i] = (Edge){v, w, head[u]};
		head[u] = i;
		++deg[v];
	}
	for (t = 1; t <= n; ++t) {
		for (u = 1; u <= n && deg[u]; ++u);
		deg[u] = -1;
		if (marken[u]) {
			if (u == s) {
				for (i = head[u]; i; i = e[i].next) {
					--deg[v = e[i].to];
					marken[v] = 1;
					f[v][1][e[i].w % 2] = a[1];
				}
			}
			else {
				for (i = head[u]; i; i = e[i].next) {
					--deg[v = e[i].to];
					marken[v] = 1;
				}
				
				++count;
				for (j = 1; j <= count; ++j) {
					if (f[u][j][0] > 0) {
						tmp = f[u][j][0];
						if (tmp * ansd > ansn * j) {
							ansd = j;
							ansn = tmp;
						}
						for (i = head[u]; i; i = e[i].next) {
							v = e[i].to;
							cmax(f[v][j][e[i].w % (j + 1)], tmp + a[j]);
							cmax(f[v][j + 1][e[i].w % (j + 2)], tmp + a[j + 1]);
						}
					}
					for (k = 1; k <= j; ++k) {
						if (f[u][j][k] > 0) {
							tmp = f[u][j][k] + a[j];
							for (i = head[u]; i; i = e[i].next) {
								cmax(f[e[i].to][j][(k + e[i].w) % (j + 1)], tmp);
							}
						}
					}
				}
			}
		}
	}
	tmp = gcd(ansn, ansd);
	printf("%lld %lld\n", ansn / tmp, ansd / tmp);
	return 0;
}
