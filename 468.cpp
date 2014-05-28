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

#define inf 0x3F3F3F3F
#define fst first
#define snd second
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
template <typename T> T gcd(T x, T y) {for (T t; x; ) t = x, x = y % x, y = t; return y; }

template<class edge> struct Graph {
    vector<vector<edge> > adj;
    Graph(int n) {adj.clear(); adj.resize(n + 5);}
    Graph() {adj.clear(); }
    void resize(int n) {adj.resize(n + 5); }
    void add(int s, edge e){adj[s].push_back(e);}
    void del(int s, edge e) {adj[s].erase(find(iter(adj[s]), e)); }
    vector<edge>& operator [](int t) {return adj[t];}
};

const int n = 11111111, N = n + 100, MOD = 1000000993;

int prime[N], lnk[N];
int64 s[N];

struct node {
    int64 a, b;
} ;

node st[N * 4];

void update(node *t, node *l, node *r) {
    t->b = (l->a * r->b + l->b) % MOD;
    t->a = (l->a * r->a) % MOD;
}

void modify(int L, int R, int t, int x, int c) {
    if (L + 1 == R) {
        (st[t].a *= c) %= MOD;
        (st[t].b *= c) %= MOD;
        return ;
    }
    int m = (L + R + 1) >> 1, lc = t << 1, rc = t << 1 | 1;
    if (x <= m) modify(L, m, lc, x, c);
    else modify(m, R, rc, x, c);
    
    update(st + t, st + lc, st + rc);
}

int query() {
    return st[1].b;
}

void add(int x, int sgn) {
    for (; x != 1; ) {
        int p = lnk[x], c = 1;
        for (; x % p == 0; x /= p)
            c *= p;
        if (sgn < 0) c = fpm(c, MOD - 2, MOD);
        modify(0, n, 1, p, c);
    }
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    for (int i = 2; i <= n; ++i) {
        if (!prime[i]) prime[++prime[0]] = i, lnk[i] = i;
        for (int j = 1, k = n / i, t; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = 1, lnk[t] = prime[j];
            if (i % prime[j] == 0) break;
        }
    }

    for (int i = 1; i < N * 4; ++i)
        st[i].a = st[i].b = 1;
    for (int i = 1; i <= n; ++i)
        modify(0, n, 1, i, 1);
    int64 ans = 0;
    
    for (int i = 0; i <= n; ++i) {
        ans += query();
        if (i < n) {
            add(n - i, +1);
            add(i + 1, -1);
        }
        if (i % 100000 == 0)
            cout << i << endl;
    }
    cout << ans % MOD << endl;

    return 0; 
}
