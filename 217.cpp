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

const int64 MOD = fpm(3, 15, 1e9);
const int n = 47, N = 50, M = 500;

int64 f[N][M], g[N][M];

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    f[0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= i * 9; ++j)
            for (int k = 0; k <= 9 && k <= j; ++k) {
                (f[i][j] += f[i - 1][j - k]) %= MOD;
                (g[i][j] += g[i - 1][j - k] * 10 + k * f[i - 1][j - k]) %= MOD;
            }

    int64 ans = 45;
    for (int i = 2; i <= n; ++i) {
        int T = i / 2, p = i & 1 ? 10 : 1;
        for (int s = 0; s <= T * 9; ++s) {
            for (int x = 1; x <= 9 && x <= s; ++x) {
                ans += g[T][s] * f[T - 1][s - x] % MOD * p % MOD;
                if (i & 1)
                    ans += 45 * f[T - 1][s - x] % MOD * f[T][s] % MOD * fpm(10, T, MOD) % MOD;
                ans += g[T - 1][s - x] * p % MOD * f[T][s] % MOD * fpm(10, T, MOD) % MOD * p;
                ans += x * fpm(10, i - 1, MOD) % MOD * f[T][s] % MOD * f[T - 1][s - x] % MOD * p % MOD;
            }
        }
    }
    cout << ans % MOD << endl;

    return 0; 
}
