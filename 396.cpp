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

const int MOD = 1e9; // fpm(5, 9, oo);

// int f(int x, int64 t) {
//     if (x == 0) return t + 1;
//     FOR (i, 1, t) t = f(x - 1, t);
//     return t;
// }

int phi(int x) {
    if (x % 2 == 0) x /= 2;
    if (x % 5 == 0) x = x / 5 * 4;
    return x;
}

struct node {
    int d; int64 t, M;
    node(int _d, int64 _t, int64 _M) : d(_d), t(_t), M(_M) {}
};

bool operator < (const node &a, const node &b) {
    if (a.d != b.d) return a.d < b.d;
    if (a.t != b.t) return a.t < b.t;
    return a.M < b.M;
}

map<node, int> F;

// int f3(int d, int64 t, int64 M) {
//     FOR (i, 1, t) {
//         (t = t * fpm(2, t, M)) %= M;
//     }
//     return M;
// }

int f3(int d, int64 t, int64 M) {
    if (M == 1) return 0;
    node n(d, t, M);
    if (F.count(n)) return F[n];
    if (d == 0) return t % M;
    int64 p = phi(M);
    int64 x = f3(d - 1, t, p);
    return F[n] = fpm(2, x, M) * (f3(d - 1, t, M)) % M;
}

// f(3, t) = 2^(2^(2^t * t) * 2^t * t + 2^t * t + t) * t
int f(int x, int64 t, int M) {
    // cerr << x << " " << t << " " << M << endl;
    if (M == 1) return 0;
    if (x == 0) return (t + 1) % M;
    if (x == 1) return t * 2 % M;
    if (x == 2) return fpm(2, t, M) * t % M;
    if (x == 3) {
        return f3(t, t, M);
    }
    assert(0);
}

int g(int x) {
    int t = 3;
    FOR (i, 0, 4) {
        if (x >> i & 1) {
            t = f(i, t, MOD);
        }
    }
    return t - 3;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    int ans = 0;
    f3(3, 2048, MOD);
    FOR (i, 1, 15) {
        // cerr << g(i) << endl;
        (ans += g(i)) %= MOD;
    }
    cerr << ans << endl;
    // FOR (i, 1, 15) {
    //     cerr << f(2, i) << " " << (1 << i) * i << endl;
    // }

    return 0; 
}
