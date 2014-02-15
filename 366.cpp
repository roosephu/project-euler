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
    Graph(int n) {adj.clear(); adj.resize(n + 5);}
    Graph() {adj.clear(); }
    void resize(int n) {adj.resize(n + 5); }
    void add(int s, edge e){adj[s].push_back(e);}
    void del(int s, edge e) {adj[s].erase(find(iter(adj[s]), e)); }
    vector<edge>& operator [](int t) {return adj[t];}
};

const int64 N = 1e2, MOD = 1e8;

int calc_sum(int64 L, int64 R) {
    int64 a = R - L, b = R + L + 1;
    if (a & 1) b >>= 1; else a >>= 1;
    return (a % MOD) * (b % MOD) % MOD;
}

struct node *null;

struct node {
    node *lc, *rc;
    int64 L, R, sum, len;

    node(int64 l, int64 r) : lc(null), rc(null), L(l), R(r), sum(calc_sum(l, r)), len(R - L) {}
    node(node *x) {*this = *x; }

    node *update() {
        sum = (lc->sum + rc->sum + calc_sum(L, R)) % MOD;
        len = lc->len + rc->len + R - L;
        return this;
    }
} ;

node *merge(node *L, node *R) {
    if (L == null) return R;
    if (R == null) return L;
    node *t;
    if (drand48() < 1.0 * L->len / (L->len + R->len)) {
        t = new node(L);
        t->rc = merge(t->rc, R);
    } else {
        t = new node(R);
        t->lc = merge(L, t->lc);
    }
    return t->update();
}

void split(node *t, int64 x, node *&L, node *&R) {
    if (t == null) {
        L = R = null;
    } else if (t->lc->len >= x) {
        R = new node(t);
        split(t->lc, x, L, R->lc);
        R->update();
    } else if (t->lc->len + t->R - t->L >= x) {
        x -= t->lc->len;
        L = merge(t->lc, new node(t->L, t->L + x));
        R = merge(new node(t->L + x, t->R), t->rc);
    } else {
        L = new node(t);
        split(t->rc, x - t->lc->len - t->R + t->L, L->rc, R);
        L->update();
    }
}

// int f[N + 1];

int64 calc(int64 n) {
    int64 a = n, b = n - 1;
    return a * b / 2;
}

// void bf() {
//     int64 a = 1, b = 1, ans = 0;
//     memset(f, -1, sizeof(f));
//     // const int N = 100;
    
//     for (; b <= N; ) {
//         int64 c = a + b;
//         f[b] = 0;
//         a = b, b = c;
//     }
//     int lx = 1;
//     FOR (i, 1, N) {
//         if (f[i] != -1) {
//             // cerr << f[i] << " ";
//             lx = i;
//             continue;
//         }
//         f[i] = i - lx;
//         if (f[i] * 2 >= lx) f[i] = f[i - lx];
//         // cerr << f[i] << " ";
//         ans += f[i];
//     }
//     cerr << "bf: " << ans << endl;
//     // cerr << ans % MOD << endl;
// }

void dfs(node *t) {
    if (t == null) return ;
    dfs(t->lc);
    FOR (i, t->L + 1, t->R) cerr << i << " ";
    dfs(t->rc);
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    null = new node(0, 0);
    null->lc = null->rc = null;
    // bf();
    auto root = new node(-1, 0);

    int64 a = 1, b = 2;
    for (; b <= N; ) {
        swap(a, b), b += a;     // construct (a, b]
        auto p = (a - 1) / 2;
        node *u, *m, *v;
        split(root, p, u, m);
        split(m, b - a - p - 1, m, v);
        root = merge(root, new node(-1, p));
        root = merge(root, m);
    }
    node *t;
    split(root, N, root, t);
    cerr << "ok: " << root->sum << endl;
    dfs(root), cerr << endl;

    return 0; 
}
