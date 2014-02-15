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

#include <gmpxx.h>

const int64 N = 1e12 / 4;

typedef mpz_class ZZ;
// typedef int64 ZZ;

ZZ cb[70][70], f[70];

void dfs(int b, int o) {
    if (b < 0) return ;
    dfs(b - 1, o + (N >> b & 1));
    if (~N >> b & 1) return ;
    for (int i = 0; i <= b; ++i) {
        f[i + o] += cb[b][i];
    }
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < 64; ++i)
        for (int j = 0; j <= i; ++j)
            cb[i][j] = j ? cb[i - 1][j - 1] + cb[i - 1][j] : (ZZ)1;
    dfs(60, 0);

    ZZ ans = 0;
    for (int i = 60; i >= 0; --i)
        ans = ans * 2 + f[i];
    cout << ans << " " << N << endl;

    return 0; 
}
