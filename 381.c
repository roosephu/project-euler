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

#define n 100000000
#define N (n + 1)

int prime[N];

int inv(int a, int b)
{
	return a != 1 ? (int64)inv(b % a, b) * (b - b / a) % b : 1;
}

int calc(int x)
{
	/* printf("%d\n", inv(5, 7)); */
	/* return 1; */
	int ret = 0, lx = x - 1, i;
	for (i = 1; i <= 5; ++i) {
		/* printf(" -> %d\n", lx); */
		ret = ret + lx;
		if (x != i) lx = (int64)lx * inv(x - i, x) % x;
	}
	return ret % x;
}

int main ()
{
	int i = 1, j, k, t;

	int64 ans = 0;
	
	for (i = 2; i <= n; ++i) {
		if (!prime[i]) {
			prime[++prime[0]] = i;
			if (i >= 5) {
				ans += calc(i);
			}
		}
		for (j = 1, k = n / i; prime[j] <= k; ++j) {
			prime[t = prime[j] * i] = 1;
			if (i % prime[j] == 0) break;
		}
	}

	printf("%lld\n", ans);
	return 0; 
}
