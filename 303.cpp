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

const int n = 10000, M = 1594323;

int64 g[M];
map<int, int64> f;

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    int64 ans = 0;
    for (int i = 1; i < M; ++i)
        g[i] = g[i / 3] * 10 + i % 3;
    for (int i = 1, j; i <= n; ++i) {
        for (j = 1; j < M && g[j] % i != 0; ++j)
            ;
        // assert(j < M);
        if (j == M) {
            cout << i << endl;
            f.clear();
            for (int x = 0; x < M; ++x) {
                int y = g[x] % i;
                if (f.count(y) == 0)
                    f[y] = g[x];
            }
            for (int x = 0; x < M; ++x) {
                int L = g[x] * fpm(10, 13, i) % i;
                if (f.count(i - L)) {
                    if (i != 9999)
                        ans += (g[x] * fpm(10, 13, 1e18) + f[i - L]) / i;
                    cout << g[x] << f[i - L] << endl;
                    break;
                }
            }
            continue;
        }
        ans += g[j] / i;
    }
    cout << ans << endl;

    return 0; 
}
