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
#define For(i, a, b) for (int _end_ = (b), i = (a); i <= _end_; ++i)
#define Rof(i, a, b) for (int _end_ = (b), i = (a); i >= _end_; --i)
#define FOR(i, a, b) for (int _end_ = (b), i = (a); i != _end_; ++i)
#define ROF(i, a, b) for (int _end_ = (b), i = (a); i != _end_; --i)

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

const int64 N = 1e10, LMT = 1e5;

int prime[LMT * 2 + 1], mu[LMT * 2 + 1], S[LMT * 2];
map<int64, int64> g;
map<pair<int, int64>, int64> f;

int64 calc(int64 x) {
    if (g.count(x)) return g[x];
    int64 &t = g[x];
    for (int64 i = 1; i * i <= x; ++i)
        t += x / i / i * mu[i];
    return t;
}

int64 dfs(int i, int64 j) {
    auto x = make_pair(i, j);
    if (f.count(x)) return f[x];
    if ((int64)S[i] * S[i] > j) return calc(j) - i;
    return f[x] = 1 + dfs(i, j / S[i]) + dfs(i + 1, j);
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    
    mu[1] = 1;
    FOR (i, 2, LMT * 2 + 1) {
        if (!prime[i]) prime[++prime[0]] = i, mu[i] = -1;
        for (int j = 1, t, k = LMT / i; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = 1;
            if (i % prime[j]) mu[t] = -mu[i];
            else {mu[t] = 0; break; }
        }
        if (mu[i]) S[++S[0]] = i;
    }
    cerr << dfs(1, N) << endl;

    return 0; 
}

