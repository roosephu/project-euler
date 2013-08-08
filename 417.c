#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#ifndef ONLINE_JUDGE
#define DEBUG
#endif
int less (int *a, int *b) {return *a < *b ? -1 : 1;}
int greater (int *a, int *b) {return *a > *b ? -1 : 1;}
typedef int (*cmp_t) (const void *, const void *);
typedef unsigned uint;
typedef long long int64;
typedef unsigned long long uint64;
#define max(i, j) ({int _ = (i), __ = (j); _ > __ ? _ : __;})
#define min(i, j) ({int _ = (i), __ = (j); _ < __ ? _ : __;})
#define swap(T, i, j) ({T _ = (i); (i) = (j); (j) = _;})
#define oo 0x3F3F3F3F
#ifdef DEBUG
#define cerr(...) fprintf (stderr, __VA_ARGS__)
#define cvar(x) cerr ("<" #x ": %d>", x)
#define evar(x) cerr ("<" #x ": %d>\n", x)
#define ctime() fprintf (stderr, "time: %.3f s\n", 1.0 * clock () / CLOCKS_PER_SEC)
void DISP (char *s, int *x, int n) {int i; cerr ("[%s: ", s); for (i = 0; i < n - 1; ++i) cerr ("%d ", x[i]); if (n) cerr ("%d", x[i]); cerr ("]\n");}
#define disp(T,n) DISP (#T " to " #n, T, n)
#else
#define cerr(...) ({})
#define cvar(...) ({})
#define evar(...) ({})
#define disp(...) ({})
#define ctime() ({})
#endif
#define CR cerr ("\n")
#ifdef WIN32
#define fmt64 "%I64d"
#else
#define fmt64 "%lld"
#endif

#define n 100000000
#define N (n + 1)
#define P 6000000

int *head, *next, *prime, *phi, *val, *len, *lnk;

int64 fpm(int64 b, int64 e, int64 m)
{
	int64 t = 1;
	for (; e; e >>= 1, b = b * b % m)
		e & 1 ? t = t * b % m : 0;
	return t;
}

#define testBit(p,x) (p[(x) >> 5] >> ((x) & 31) & 1)
#define setBit(p,x) (p[(x) >> 5] |= 1u << ((x) & 31))

int find(int x) 
{
	int a, b, ret = 0;
	for (a = 1; a <= x; a *= 2) {
		for (b = a; b <= x; b *= 5) {
			++ret;
		}
	}
	return ret;
}

int gcd(int a, int b)
{
	return a ? gcd(b % a, a) : b;
}

int main ()
{
	int i, j, k, t;
	int64 total = 0;

	prime = calloc(N, sizeof(int));
	phi = calloc(N, sizeof(int));
	lnk = calloc(N, sizeof(int));

	for (i = 2; i <= n; ++i) {
		if (!prime[i]) {
			prime[++prime[0]] = i;
			phi[i] = i - 1;
			lnk[i] = 1;
		}
		for (j = 1, k = n / i; prime[j] <= k; ++j) {
			prime[t = prime[j] * i] = 1;
			if (i % prime[j]) {
				phi[t] = phi[i] * phi[prime[j]];
				lnk[t] = i;
			} else {
				phi[t] = phi[i] * prime[j];
				lnk[t] = lnk[i];
				break;
			}
		}
	}

	head = prime;
	memset(head, 0, N * sizeof(int));
	val = calloc(P, sizeof(int));
	next = calloc(P, sizeof(int));

	int top = 0;
	for (i = 1; i <= n; ++i) {
		if (i % 2 == 0 || i % 5 == 0 || lnk[i] != 1) continue;
		++top;
		int f = phi[i];
		/* printf("phi %d %d\n", i, f); */
		next[top] = head[f];
		head[f] = top;
		val[top] = i;
	}
	len = phi;
	memset(len, 0, N * sizeof(len));
	/* assert(top <= P); */
	/* printf("%d\n", top); */
	/* return 0; */

	for (i = 1; i <= n; ++i) {
		for (j = i; j <= n; j += i) {
			int h = head[j];
			for (; h; h = next[h]) {
				int v = val[h];
				if (!len[v] && fpm(10, i, v) == 1) {
					len[v] = i;
				}
			}
		}
	}
	
	for (i = 2; i <= n; ++i) {
		if (i % 2 == 0) {
			len[i] = len[i / 2];
		} else if (i % 5 == 0) {
			len[i] = len[i / 5];
		} else if (lnk[i] != 1) {
			int a = len[i / lnk[i]], b = len[lnk[i]];
			len[i] = a * b / gcd(a, b);
		}
		total += len[i];
	}

	/* for (i = 1; i <= n; ++i) { */
	/* 	if (i % 2 != 0 && i % 5 != 0) { */
	/* 		for (j = 2; j * j <= i; ++j) { */
	/* 			if (i % j == 0) { */
	/* 				int k = 1, t = i; */
	/* 				for (; t % j == 0; k *= j, t /= j); */
	/* 				if (t == 1) break; */
	/* 				/\* printf("%d %d %d %d %d %d\n", i, k, t, len[i], len[k], len[t]); *\/ */
	/* 				assert(len[i] == len[k] * len[t] / gcd(len[k], len[t])); */
	/* 				break; */
	/* 			} */
	/* 		} */
	/* 	} */
	/* } */

	printf("ans: %lld\n", total);
	return 0; 
}
