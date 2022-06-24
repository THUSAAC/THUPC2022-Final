#include <cstdio>
#include <cstring>
using namespace std;
#define MOD 1000000007
struct MAT {
	int a[306][306], siz;
	MAT() {
		memset(a, 0, sizeof(a));
		siz = 0;
	}
	inline MAT operator *(const MAT &x) const {
		int i, j, k, *C;
		const int *B;
		long long tmp;
		MAT ret;
		// assert siz == x.siz
		ret.siz = siz;
		for (i = 0; i < siz; ++i) {
			for (j = 0; j < siz; ++j) {
				if (tmp = a[i][j]) {
					for (k = 0, B = x.a[j], C = ret.a[i]; k < siz; ++k, ++B, ++C) *C = (*C + tmp * *B) % MOD;
				}
			}
		}
		return ret;
	}
	void pr() const {
		fprintf(stderr, "===\n");
		for (int i = 0; i < siz; ++i) {
			for (int j = 0; j < siz; ++j) {
				fprintf(stderr, "%d%c", a[i][j], " \n"[j == siz - 1]);
			}
		}
		fprintf(stderr, "===\n");
		return ;
	}
} M[30], D[30], L[30];
int drep[18][18], dinc[18][27], ddec[18][27], lrep[27][18], linc[27][27], ldec[27][27];
int vec[36][306];
#define INDEX(_len, _pos) ((_pos) >= ((_len) / 2) ? ((_len) - 1 - (_pos)) : (_pos))
void MatVec(int *res, const MAT &x, const int *v){
	int i, j;
	memset(res, 0, sizeof(int) * x.siz);
	for (i = 0; i < x.siz; ++i, ++res) {
		for (j = 0; j < x.siz; ++j) {
			*res = (*res + 1ll * x.a[i][j] * v[j]) % MOD;
		}
	}
	return ;
}
int Calc(const MAT *x, int exp){
	int cnt = 0, index;
	for (index = 0; exp; ++index, exp >>= 1) {
		if (exp & 1) {
			MatVec(vec[cnt + 1], x[index], vec[cnt]);
			++cnt;
		}
	}
	return vec[cnt][x[0].siz - 1];
}
int main(){
	int l, r, a, b, c, t, i, j, mtot = 0, dtot = 0, ltot = 0, ans = 0, id, nowc;
	scanf("%d %d %d %d", &l, &r, &a, &b);
	// Initializing M
	for (c = 0; c < 5; ++c) {	// '0' - '4'
		for (i = 1; i < a; ++i) drep[c][i] = mtot++;
		if (c + b <= 10) {
			for (i = 2; i < b; ++i) dinc[c][i] = mtot++;
		}
		if (c >= b - 1) {
			for (i = 2; i < b; ++i) ddec[c][i] = mtot++;
		}
		else if (c > 0) ddec[c][2] = drep[c - 1][1];
	}
	for (c = 0; c < 5; ++c) {
		if (c + b > 10) dinc[c][2] = drep[INDEX(10, c + 1)][1];
	}
	for (c = 5; c < 10; ++c) {	// '5' - '9'
		drep[c][1] = drep[INDEX(10, c)][1];
		drep[c][2] = drep[INDEX(10, c)][2];
		dinc[c][2] = ddec[INDEX(10, c)][2];
		ddec[c][2] = dinc[INDEX(10, c)][2];
	}
	for (c = 0; c < 13; ++c) {	// 'a' - 'm'
		for (i = 1; i < a; ++i) lrep[c][i] = mtot++;
		if (c + b <= 26) {
			for (i = 2; i < b; ++i) linc[c][i] = mtot++;
		}
		if (c >= b - 1) {
			for (i = 2; i < b; ++i) ldec[c][i] = mtot++;
		}
		else if (c > 0) ldec[c][2] = lrep[c - 1][1];
	}
	for (c = 0; c < 13; ++c) {	// 'a' - 'm'
		if (c + b > 26) linc[c][2] = lrep[INDEX(26, c + 1)][1];
	}
	for (c = 13; c < 26; ++c) {	// 'n' - 'z'
		lrep[c][1] = lrep[INDEX(26, c)][1];
		lrep[c][2] = lrep[INDEX(26, c)][2];
		linc[c][2] = ldec[INDEX(26, c)][2];
		ldec[c][2] = linc[INDEX(26, c)][2];
	}
	M[0].siz = ++mtot;	// sum
	
	for (c = 0; c < 5; ++c) {	// digit
		for (i = 1; i < a; ++i) {	// repeating seq
			id = drep[c][i];
			for (t = 0; t < 10; ++t) {	// digit -> digit
				if (t == c - 1) {
					if (b > 2) M[0].a[ddec[c][2]][id] += 1;
				}
				else if (t == c) {
					if (i + 1 < a) M[0].a[drep[c][i + 1]][id] += 1;
				}
				else if (t == c + 1) {
					if (b > 2) M[0].a[dinc[c][2]][id] += 1;
				}
				else {
					M[0].a[drep[INDEX(10, t)][1]][id] += 1;
				}
			}
			for (t = 0; t < 26; ++t) {	// digit -> letter, both big and small cases
				M[0].a[lrep[INDEX(26, t)][1]][id] += 2;
			}
			M[0].a[mtot - 1][id] += 1;
		}
		if (c + b <= 10) {
			for (i = 2; i < b; ++i) {	// increasing seq
				id = dinc[c][i];
				nowc = c + i - 1;
				for (t = 0; t < 10; ++t) {	// digit -> digit, current c + i - 1
					if (t == nowc - 1) {
						if (b > 2) M[0].a[ddec[nowc][2]][id] += 1;
					}
					else if (t == nowc) {
						if (a > 2) M[0].a[drep[nowc][2]][id] += 1;
					}
					else if (t == nowc + 1) {
						if (i + 1 < b) M[0].a[dinc[c][i + 1]][id] += 1;
					}
					else {
						M[0].a[drep[INDEX(10, t)][1]][id] += 1;
					}
				}
				for (t = 0; t < 26; ++t) {	// digit -> letter, both big and small cases
					M[0].a[lrep[INDEX(26, t)][1]][id] += 2;
				}
				M[0].a[mtot - 1][id] += 1;
			}
		}
		if (c >= b - 1) {
			for (i = 2; i < b; ++i) {	// decreasing seq
				id = ddec[c][i];
				nowc = c - i + 1;
				for (t = 0; t < 10; ++t) {	// digit -> digit
					if (t == nowc - 1) {
						if (i + 1 < b) M[0].a[ddec[c][i + 1]][id] += 1;
					}
					else if (t == nowc) {
						if (a > 2) M[0].a[drep[nowc][2]][id] += 1;
					}
					else if (t == nowc + 1) {
						if (b > 2) M[0].a[dinc[nowc][2]][id] += 1;
					}
					else {
						M[0].a[drep[INDEX(10, t)][1]][id] += 1;
					}
				}
				for (t = 0; t < 26; ++t) {	// digit -> letter, both big and small cases
					M[0].a[lrep[INDEX(26, t)][1]][id] += 2;
				}
				M[0].a[mtot - 1][id] += 1;
			}
		}
	}
	
	for (c = 0; c < 13; ++c) {	// letter
		for (i = 1; i < a; ++i) {	// repeating seq
			id = lrep[c][i];
			for (t = 0; t < 26; ++t) {	// letter -> letter, same case
				if (t == c - 1) {
					if (b > 2) M[0].a[ldec[c][2]][id] += 1;
				}
				else if (t == c) {
					if (i + 1 < a) M[0].a[lrep[c][i + 1]][id] += 1;
				}
				else if (t == c + 1) {
					if (b > 2) M[0].a[linc[c][2]][id] += 1;
				}
				else {
					M[0].a[lrep[INDEX(26, t)][1]][id] += 1;
				}
			}
			for (t = 0; t < 26; ++t) {	// letter -> letter, different cases
				M[0].a[lrep[INDEX(26, t)][1]][id] += 1;
			}
			for (t = 0; t < 10; ++t) {	// letter -> digit
				M[0].a[drep[INDEX(10, t)][1]][id] += 1;
			}
			M[0].a[mtot - 1][id] += 1;
		}
		if (c + b <= 26) {
			for (i = 2; i < b; ++i) {	// increasing seq
				id = linc[c][i];
				nowc = c + i - 1;
				for (t = 0; t < 26; ++t) {	// letter -> letter, same case
					if (t == nowc - 1) {
						if (b > 2) M[0].a[ldec[nowc][2]][id] += 1;
					}
					else if (t == nowc) {
						if (a > 2) M[0].a[lrep[nowc][2]][id] += 1;
					}
					else if (t == nowc + 1) {
						if (i + 1 < b) M[0].a[linc[c][i + 1]][id] += 1;
					}
					else {
						M[0].a[lrep[INDEX(26, t)][1]][id] += 1;
					}
				}
				for (t = 0; t < 26; ++t) {	// letter -> letter, different cases
					M[0].a[lrep[INDEX(26, t)][1]][id] += 1;
				}
				for (t = 0; t < 10; ++t) {	// letter -> digit
					M[0].a[drep[INDEX(10, t)][1]][id] += 1;
				}
				M[0].a[mtot - 1][id] += 1;
			}
		}
		if (c >= b - 1) {
			for (i = 2; i < b; ++i) {	// decreasing seq
				id = ldec[c][i];
				nowc = c - i + 1;
				for (t = 0; t < 26; ++t) {	// letter -> letter, same case
					if (t == nowc - 1) {
						if (i + 1 < b) M[0].a[ldec[c][i + 1]][id] += 1;
					}
					else if (t == nowc) {
						if (a > 2) M[0].a[lrep[nowc][2]][id] += 1;
					}
					else if (t == nowc + 1) {
						if (b > 2) M[0].a[linc[nowc][2]][id] += 1;
					}
					else {
						M[0].a[lrep[INDEX(26, t)][1]][id] += 1;
					}
				}
				for (t = 0; t < 26; ++t) {	// letter -> letter, different cases
					M[0].a[lrep[INDEX(26, t)][1]][id] += 1;
				}
				for (t = 0; t < 10; ++t) {	// letter -> digit
					M[0].a[drep[INDEX(10, t)][1]][id] += 1;
				}
				M[0].a[mtot - 1][id] += 1;
			}
		}
	}
	
	M[0].a[mtot - 1][mtot - 1] = 1;
	for (i = 1, j = 2; j <= r; ++i, j <<= 1) M[i] = M[i - 1] * M[i - 1];
	// Calculate answer about M, first init vec
	memset(vec, 0, sizeof(vec));
	for (c = 0; c < 10; ++c) vec[0][drep[INDEX(10, c)][1]] += 1;
	for (c = 0; c < 26; ++c) vec[0][lrep[INDEX(26, c)][1]] += 2;
	ans = (ans + MOD - Calc(M, l - 1)) % MOD;
	
	memset(vec, 0, sizeof(vec));
	for (c = 0; c < 10; ++c) vec[0][drep[INDEX(10, c)][1]] += 1;
	for (c = 0; c < 26; ++c) vec[0][lrep[INDEX(26, c)][1]] += 2;
	ans = (ans + Calc(M, r)) % MOD;
	// Initial D
	for (c = 0; c < 5; ++c) {	// '0' - '4'
		for (i = 1; i < a; ++i) drep[c][i] = dtot++;
		if (c + b <= 10) {
			for (i = 2; i < b; ++i) dinc[c][i] = dtot++;
		}
		if (c >= b - 1) {
			for (i = 2; i < b; ++i) ddec[c][i] = dtot++;
		}
		else if (c > 0) ddec[c][2] = drep[c - 1][1];
	}
	for (c = 0; c < 5; ++c) {
		if (c + b > 10) dinc[c][2] = drep[INDEX(10, c + 1)][1];
	}
	for (c = 5; c < 10; ++c) {	// '5' - '9'
		drep[c][1] = drep[INDEX(10, c)][1];
		drep[c][2] = drep[INDEX(10, c)][2];
		dinc[c][2] = ddec[INDEX(10, c)][2];
		ddec[c][2] = dinc[INDEX(10, c)][2];
	}
	D[0].siz = ++dtot;	// sum
	
	for (c = 0; c < 5; ++c) {	// digit
		for (i = 1; i < a; ++i) {	// repeating seq
			id = drep[c][i];
			for (t = 0; t < 10; ++t) {	// digit -> digit
				if (t == c - 1) {
					if (b > 2) D[0].a[ddec[c][2]][id] += 1;
				}
				else if (t == c) {
					if (i + 1 < a) D[0].a[drep[c][i + 1]][id] += 1;
				}
				else if (t == c + 1) {
					if (b > 2) D[0].a[dinc[c][2]][id] += 1;
				}
				else {
					D[0].a[drep[INDEX(10, t)][1]][id] += 1;
				}
			}
			D[0].a[dtot - 1][id] += 1;
		}
		if (c + b <= 10) {
			for (i = 2; i < b; ++i) {	// increasing seq
				id = dinc[c][i];
				nowc = c + i - 1;
				for (t = 0; t < 10; ++t) {	// digit -> digit, current c + i - 1
					if (t == nowc - 1) {
						if (b > 2) D[0].a[ddec[nowc][2]][id] += 1;
					}
					else if (t == nowc) {
						if (a > 2) D[0].a[drep[nowc][2]][id] += 1;
					}
					else if (t == nowc + 1) {
						if (i + 1 < b) D[0].a[dinc[c][i + 1]][id] += 1;
					}
					else {
						D[0].a[drep[INDEX(10, t)][1]][id] += 1;
					}
				}
				D[0].a[dtot - 1][id] += 1;
			}
		}
		if (c >= b - 1) {
			for (i = 2; i < b; ++i) {	// decreasing seq
				id = ddec[c][i];
				nowc = c - i + 1;
				for (t = 0; t < 10; ++t) {	// digit -> digit
					if (t == nowc - 1) {
						if (i + 1 < b) D[0].a[ddec[c][i + 1]][id] += 1;
					}
					else if (t == nowc) {
						if (a > 2) D[0].a[drep[nowc][2]][id] += 1;
					}
					else if (t == nowc + 1) {
						if (b > 2) D[0].a[dinc[nowc][2]][id] += 1;
					}
					else {
						D[0].a[drep[INDEX(10, t)][1]][id] += 1;
					}
				}
				D[0].a[dtot - 1][id] += 1;
			}
		}
	}
	
	D[0].a[dtot - 1][dtot - 1] = 1;
	for (i = 1, j = 2; j <= r; ++i, j <<= 1) D[i] = D[i - 1] * D[i - 1];
	// Calculate answer about D, first init vec
	memset(vec, 0, sizeof(vec));
	for (c = 0; c < 10; ++c) vec[0][drep[INDEX(10, c)][1]] += 1;
	ans = (ans + Calc(D, l - 1)) % MOD;
	
	memset(vec, 0, sizeof(vec));
	for (c = 0; c < 10; ++c) vec[0][drep[INDEX(10, c)][1]] += 1;
	ans = (ans + MOD - Calc(D, r)) % MOD;
	
	
	// Initializing L
	for (c = 0; c < 13; ++c) {	// 'a' - 'm'
		for (i = 1; i < a; ++i) lrep[c][i] = ltot++;
		if (c + b <= 26) {
			for (i = 2; i < b; ++i) linc[c][i] = ltot++;
		}
		if (c >= b - 1) {
			for (i = 2; i < b; ++i) ldec[c][i] = ltot++;
		}
		else if (c > 0) ldec[c][2] = lrep[c - 1][1];
	}
	for (c = 0; c < 13; ++c) {	// 'a' - 'm'
		if (c + b > 26) linc[c][2] = lrep[INDEX(26, c + 1)][1];
	}
	for (c = 13; c < 26; ++c) {	// 'n' - 'z'
		lrep[c][1] = lrep[INDEX(26, c)][1];
		lrep[c][2] = lrep[INDEX(26, c)][2];
		linc[c][2] = ldec[INDEX(26, c)][2];
		ldec[c][2] = linc[INDEX(26, c)][2];
	}
	L[0].siz = ++ltot;	// sum
	
	for (c = 0; c < 13; ++c) {	// letter
		for (i = 1; i < a; ++i) {	// repeating seq
			id = lrep[c][i];
			for (t = 0; t < 26; ++t) {	// letter -> letter, same case
				if (t == c - 1) {
					if (b > 2) L[0].a[ldec[c][2]][id] += 1;
				}
				else if (t == c) {
					if (i + 1 < a) L[0].a[lrep[c][i + 1]][id] += 1;
				}
				else if (t == c + 1) {
					if (b > 2) L[0].a[linc[c][2]][id] += 1;
				}
				else {
					L[0].a[lrep[INDEX(26, t)][1]][id] += 1;
				}
			}
			for (t = 0; t < 26; ++t) {	// letter -> letter, different cases
				L[0].a[lrep[INDEX(26, t)][1]][id] += 1;
			}
			L[0].a[ltot - 1][id] += 1;
		}
		if (c + b <= 26) {
			for (i = 2; i < b; ++i) {	// increasing seq
				id = linc[c][i];
				nowc = c + i - 1;
				for (t = 0; t < 26; ++t) {	// letter -> letter, same case
					if (t == nowc - 1) {
						if (b > 2) L[0].a[ldec[nowc][2]][id] += 1;
					}
					else if (t == nowc) {
						if (a > 2) L[0].a[lrep[nowc][2]][id] += 1;
					}
					else if (t == nowc + 1) {
						if (i + 1 < b) L[0].a[linc[c][i + 1]][id] += 1;
					}
					else {
						L[0].a[lrep[INDEX(26, t)][1]][id] += 1;
					}
				}
				for (t = 0; t < 26; ++t) {	// letter -> letter, different cases
					L[0].a[lrep[INDEX(26, t)][1]][id] += 1;
				}
				L[0].a[ltot - 1][id] += 1;
			}
		}
		if (c >= b - 1) {
			for (i = 2; i < b; ++i) {	// decreasing seq
				id = ldec[c][i];
				nowc = c - i + 1;
				for (t = 0; t < 26; ++t) {	// letter -> letter, same case
					if (t == nowc - 1) {
						if (i + 1 < b) L[0].a[ldec[c][i + 1]][id] += 1;
					}
					else if (t == nowc) {
						if (a > 2) L[0].a[lrep[nowc][2]][id] += 1;
					}
					else if (t == nowc + 1) {
						if (b > 2) L[0].a[linc[nowc][2]][id] += 1;
					}
					else {
						L[0].a[lrep[INDEX(26, t)][1]][id] += 1;
					}
				}
				for (t = 0; t < 26; ++t) {	// letter -> letter, different cases
					L[0].a[lrep[INDEX(26, t)][1]][id] += 1;
				}
				L[0].a[ltot - 1][id] += 1;
			}
		}
	}
	
	L[0].a[ltot - 1][ltot - 1] = 1;
	for (i = 1, j = 2; j <= r; ++i, j <<= 1) L[i] = L[i - 1] * L[i - 1];
	// Calculate answer about L, first init vec
	memset(vec, 0, sizeof(vec));
	for (c = 0; c < 26; ++c) vec[0][lrep[INDEX(26, c)][1]] += 2;
	ans = (ans + Calc(L, l - 1)) % MOD;
	
	memset(vec, 0, sizeof(vec));
	for (c = 0; c < 26; ++c) vec[0][lrep[INDEX(26, c)][1]] += 2;
	ans = (ans + MOD - Calc(L, r)) % MOD;
	
	printf("%d\n", ans);
	return 0;
}
