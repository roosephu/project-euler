#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cassert>
#if __cplusplus > 201103L
#include <initializer_list>
#include <unordered_map>
#include <unordered_set>
#endif

using namespace std;

#ifndef ONLINE_JUDGE
#define DEBUG
#endif

#define oo 0x3F3F3F3F
#ifdef DEBUG
#define cvar(x) cerr << "<" << #x << ": " << x << ">"
#define evar(x) cvar (x) << endl
template<class T> void DISP(const char *s, T x, int n) {cerr << "[" << s << ": "; for (int i = 0; i < n; ++i) cerr << x[i] << " "; cerr << "]" << endl;}
#define disp(x,n) DISP(#x " to " #n, x, n)
#else
#define cvar(...) ({})
#define evar(...) ({})
#define disp(...) ({})
#endif
#define car first
#define cdr second
#define PB push_back
#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, a, b) for (int _end_ = (b), i = (a); i <= _end_; ++i)
#define ROF(i, a, b) for (int _end_ = (b), i = (a); i >= _end_; --i)

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
typedef long double real;

int64 fpm(int64 b, int64 e, int64 m) { int64 t = 1; for (; e; e >>= 1, b = b * b % m) e & 1 ? t = t * b % m : 0; return t; }
template<class T> inline bool chkmin(T &a, T b) {return a > b ? a = b, true : false;}
template<class T> inline bool chkmax(T &a, T b) {return a < b ? a = b, true : false;}
template<class T> inline T sqr(T x) {return x * x;}
template <typename T> T gcd(T x, T y) {for (T t; x; t = x, x = y % x, y = t); return y; }

template<class edge> struct Graph {
    vector<vector<edge> > adj;
    Graph(int n) {adj.clear (); adj.resize (n + 5);}
    Graph() {adj.clear (); }
    void resize(int n) {adj.resize (n + 5); }
    void add(int s, edge e){adj[s].push_back (e);}
    void del(int s, edge e) {adj[s].erase (find (iter (adj[s]), e)); }
    vector<edge>& operator [](int t) {return adj[t];}
};

const int n = 60000000;
const int lmt = 100000;

int lx, cur, cnt;
int lnk[n + 1], prime[n + 1], dd[n + 1];
int b2[lmt + 2], b1[lmt + 2];

void push(int a) {
    if (a == lx) ++cnt;
    else cur *= cnt, lx = a, cnt = 2;
}

int query(int *bit, int x) {
    int t = bit[x];
    for (; x &= x - 1; t += bit[x]);
    return t;
}

void modify(int *bit, int x, int v) {
    for (; x <= lmt; x += x & -x)
        bit[x] += v;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    int mdd = 0;
     FOR (i, 2, n + 1) {
         if (!prime[i]) prime[++prime[0]] = i, lnk[i] = i;
         for (int j = 1, t, k = (n + 1) / i; prime[j] <= k; ++j) {
             prime[t = prime[j] * i] = 1, lnk[t] = prime[j];
             if (i % prime[j] == 0) break;
         }
     }
     FOR (i, 1, n) {
         int a = i, b = i + 1;
         if (a & 1) b /= 2; else a /= 2;

         cnt = 1, lx = 0, cur = 1;
         for (; a != 1 || b != 1; ) {
             if (lnk[a] < lnk[b]) {
                 push(lnk[b]), b /= lnk[b];
             } else {
                 push(lnk[a]), a /= lnk[a];
             }
         }
         dd[i] = cnt * cur;

         chkmax(mdd, dd[i]);
         ++b2[dd[i]];
     }
     cerr << mdd << endl;
     // return 0;
     
     FOR (i, 1, lmt) {
         int x = i + (i & -i);
         if (x <= lmt) b2[x] += b2[i];
     }

     int64 ans = 0;
     FOR (i, 1, n) {
         if (i % 1048576 == 0) cerr << ans << endl;
         ans += (i - 1ll - query(b1, dd[i])) * (query(b2, dd[i] - 1));
         modify(b1, dd[i], +1);
         modify(b2, dd[i], -1);
         ans %= (int64)1e18;
     }
     cout << ans << endl;

     return 0; 
}
