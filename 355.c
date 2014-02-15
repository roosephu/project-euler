#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define DEBUG
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
#define cvar(x) cerr ("[" #x ": %d]\n", x)
void disp (char *s, int *x, int n) {int i; cerr ("[%s: ", s); for (i = 0; i < n - 1; ++i) cerr ("%d ", x[i]); if (n) cerr ("%d", x[i]); cerr ("]\n");}
#else
#define cerr(...) ({})
#define cvar(...) ({})
#define disp(...) ({})
#endif
#define CR cerr ("\n")
#ifdef WIN32
#define fmt64 "%I64d"
#else
#define fmt64 "%lld"
#endif

#define maxn 440000
#define maxv 40000

typedef struct edge {int t, w, c; struct edge *n, *o;} edge;
typedef int arr32[maxn];

edge graph[maxn << 1], *eptr = graph, *adj[maxv], *pred[maxv];
arr32 dist, next, o, val;
int prime[maxn];

int primal_dual (int S, int T)
{
  int mincost = 0, phi = 0, tms = 0;
  
  int modify_dist ()
  {
    memset (dist, 0x3F, sizeof (dist)), dist[T] = 0;
    int head = T, tail = T, v, dtmp; edge *e;
    for (v = T; e = pred[v], v; --v)
      if (e && e->o->c)
        {
          dist[v] = min (dist[v], dist[e->o->t] - e->w);
          if (head != tail && dist[next[T]] < dtmp)
            next[v] = next[T], next[T] = v;
          else
            next[tail] = v, tail = v;
        }
    
    for (; head; head = next[v], next[v] = 0)
      for (e = adj[v = head]; e; e = e->n)
        if (e->o->c && (dtmp = dist[v] - e->w) < dist[e->t])
          {
            dist[e->t] = dtmp, pred[e->t] = e;
            if (next[e->t] || tail == e->t) continue;
            if (head != tail && dist[next[v]] < dtmp)
              next[e->t] = next[v], next[v] = e->t;
            else
              next[tail] = e->t, tail = e->t;
          }
    for (v = 1; v <= T; ++v)
      for (e = adj[v]; e; e = e->n)
        e->w -= dist[v] - dist[e->t];
    phi += dist[S], cvar (phi);
    return phi < 0 && dist[S] != oo;
  }

  int augment (int v, int f)
  {
    if (v == T) return mincost += f * phi, f;
    edge *e; int w = f;
    for (e = adj[v], o[v] = tms; e; e = e->n)
      if (e->c && o[e->t] != tms && !e->w)
        {
          int x = augment (e->t, min (f, e->c));
          e->c -= x, e->o->c += x, f -= x;
          if (!f) return w;
        }
    return w - f;
  }

  for (; modify_dist (); )
    for (; ++tms, augment (S, oo); );
  return mincost;
}

void adde (int s, int t, int w, int c)
{
  /* cerr ("adde: %d %d %d %d\n", s, t, w, c); */
  *(++eptr) = (edge){t, +w, c, adj[s]}, adj[s] = eptr;
  *(++eptr) = (edge){s, -w, 0, adj[t]}, adj[t] = eptr;
  adj[s]->o = adj[t], adj[t]->o = adj[s];
}

int main ()
{
  freopen ("kissatenn.in" , "r", stdin);
  freopen ("kissatenn.out", "w", stdout);

  int n, i, j, k, t, S, T;
  
  scanf ("%d", &n);
  for (i = 2; i <= n; ++i)
    {
      if (!prime[i]) prime[++prime[0]] = i;
      for (j = 1, k = n / i; prime[j] <= k; ++j)
        {
          prime[t = i * prime[j]] = 1;
          if (i % prime[j] == 0) break;
        }
    }

  int lmt = sqrt (n), ans = 0; S = prime[0] * 2 + 1, T = S + 1;
  
  for (i = 1; i <= prime[0]; ++i)
    {
      for (j = prime[i]; j <= n && n / j >= prime[i]; j *= prime[i]);
      val[i] = j;
    }
  for (i = 1; i <= prime[0]; ++i)
    if (prime[i] > lmt)
      for (j = 1; j <= prime[0] && prime[j] <= lmt; ++j)
        if (n / prime[i] >= prime[j])
          {
            int k = prime[i] * prime[j];
            for (; n / k >= prime[j]; k *= prime[j]);
            if (k > val[j] + val[i])
              adde (i, j + prime[0], -k, 1);
        }
  for (i = 1; i <= prime[0]; ++i)
    if (adj[i] || adj[i + prime[0]])
      adde (S, i, 0, 1), adde (i, i + prime[0], -val[i], 1), adde (i + prime[0], T, 0, 1);
    else
      ans += val[i];

  cvar ((eptr - graph) / 2);
  printf ("%d\n", -primal_dual (S, T) + ans + 1);
  return 0; 
}
