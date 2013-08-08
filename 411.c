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

#define maxn 25000000
#define maxE (maxn << 1 | 5)

typedef struct edge {int t; struct edge *n; } edge;

edge graph[maxE], *eptr, *adj[maxE];
int S[maxE], Q[maxE];

int calc(int n)
{
	int top = 0;
	
	void update(int x) 
	{
		int l = 1, r = top + 1, m;
		for (; m = (l + r) >> 1, l < r; )
			S[m] <= x ? (l = m + 1) : (r = m);
		S[m] = x;
		if (m > top) top = m;
	}

	void adde(int s, int t)
	{
		*++eptr = (edge){t, adj[s]}, adj[s] = eptr;
	}

	eptr = graph;
	memset(adj, 0, sizeof(edge) * n);
	int a = 1, b = 1, i, j;
	for (i = 0; i <= n * 2; ++i) {
		adde(a, b);
		a = a * 2 % n;
		b = b * 3 % n;
	}
	for (i = 0; i < n; ++i) {
		edge *e;

		int x = 0;
		for (e = adj[i]; e; e = e->n) {
			Q[++x] = e->t;
		}
		qsort(Q + 1, x, sizeof(Q[0]), (cmp_t)less);

		Q[0] = -1;
		for (j = 1; j <= x; ++j) {
			if (Q[j] != Q[j - 1]) {
				update(Q[j]);
			}
		}
	}
	return top;
}

int main ()
{
	int i, ans = 0;
	for (i = 1; i <= 30; ++i) {
		int x = calc(i * i * i * i * i);
		printf("%d %d\n", i, x);
		ans += x;
	}
	printf("%d\n", ans);

	return 0; 
}
