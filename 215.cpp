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

const int n = 32, N = n + 3, lmt = 59049, m = 10;

int64 f[N][lmt];
int Lv, Z[m + 2];

void dfs(int p, int64 S, int64 v) {
    if (p > m) {
        f[Lv + 1][S] += v;
        return ;
    }
    if (Z[p] != 0) return dfs(p + 1, S * 3 + Z[p] - 1, v);
    if (Z[p - 1] != 2 && Z[p + 1] != 2)
        Z[p] = 2, dfs(p + 1, S * 3 + 1, v);
    if (Z[p - 1] != 3 && Z[p + 1] != 3)
        Z[p] = 3, dfs(p + 1, S * 3 + 2, v);
    Z[p] = 0;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    f[0][0] = 1;
    for (int i = 0; i < n - 3; ++i) {
        Lv = i;
        for (int s = 0; s < lmt; ++s) {
            if (!f[i][s]) continue;
            for (int x = m, S = s; x; --x) {
                Z[x] = S % 3;
                S /= 3;
            }
            dfs(1, 0, f[i][s]);
        }
        cout << i << endl;
    }

    int64 ans = 0;
    int v = n - 3;
    for (int s = 0; s < lmt; ++s) {
        bool b = true;
        for (int x = m, S = s; x; --x) {
            if (S % 3 == 2)
                b = false;
            S /= 3;
        }
        if (b) ans += f[v][s];
    }
    cout << ans << endl;

    return 0; 
}
