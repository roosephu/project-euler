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

#define n 10000000
#define N (n + 1)

int prime[N], lnk[N], nxt[N];
bool b[N];

int main ()
{
	int i, j, k, t;
	
	for (i = 2; i <= n; ++i) {
		if (!prime[i]) {
			prime[++prime[0]] = i;
			lnk[i] = 1;
			nxt[i] = i;
		}
		for (j = 1, k = n / i; prime[j] <= k; ++j) {
			prime[t = prime[j] * i] = 1;
			nxt[t] = prime[j];
			if (i % prime[j]) {
				lnk[t] = i;
			} else {
				lnk[t] = lnk[i];
				break;
			}
		}
	}

	int64 ans = 0;
	for (i = n; i; --i) {
		if (lnk[lnk[i]] == 1) {
			int v = nxt[i] * nxt[lnk[i]];
			if (b[v]) continue;
			b[v] = 1;
			ans += i;
			/* printf("%d %d %d\n", i, nxt[i], nxt[lnk[i]]); */
		}
	}
	printf("%lld\n", ans);

	return 0; 
}
