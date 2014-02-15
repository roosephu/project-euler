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

const int LMT = 1e6, MOD = 1e9;
const int64 N = 1e9;

map<int64, int64> f, g;
int64 tf[LMT + 1], tg[LMT + 1];

int64 cb(int64 n) {
    int64 a = n, b = n + 1;
    if (a & 1) b >>= 1; else a >>= 1;
    return (a % MOD) * (b % MOD) % MOD;
}

int64 F(int64 n) { // sum_{i=1}^n sum_of_divisor(i)
    if (n < LMT) return tf[n];
    if (f.count(n)) return f[n];
    auto &t = f[n]; t = 0;
    for (int64 i = 1, j; i <= n; i = j) {
        j = n / (n / i) + 1;
        t += (j - i) % MOD * cb(n / i) % MOD;
    }
    return t %= MOD;
}

int64 G(int64 n) {
    if (n < LMT) return tg[n];
    if (g.count(n)) return g[n];
    auto &t = g[n]; t = sqr(F(n)) % MOD;
    for (int64 i = 2, j; i <= n; i = j) {
        j = n / (n / i) + 1;
        (t += MOD - (cb(j - 1) - cb(i - 1) + MOD) % MOD * G(n / i) % MOD) %= MOD;
    }
    return t;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cerr << "init 1: " << endl;
    FOR (i, 1, LMT) {
        (tf[i] += tf[i - 1]) %= MOD;
        FOR (j, 1, LMT / i) {
            (tf[i * j] += i) %= MOD;
        }
    }
    cerr << "init 2: " << endl;
    FOR (i, 1, LMT) {
        (tg[i] += sqr(tf[i]) % MOD - sqr(tf[i - 1]) % MOD) %= MOD;
        FOR (j, 2, LMT / i) {
            (tg[i * j] += MOD - tg[i] * j % MOD) %= MOD;
        }
        (tg[i] += tg[i - 1]) %= MOD;
    }
    cerr << "calc: " << endl;
    cout << G(N) << endl;

    cerr << 1.0 * clock() / CLOCKS_PER_SEC << endl;
    return 0; 
}
