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

const int N = 20;

int w[N + 1];

real R(int S, real c) {
    real ret = 0, E = 0; int n = 0, t = __builtin_popcount(S);
    for (; S >> n; ++n)
        w[n + 1] = S >> n & 1;
    if (c == 0) return n;
    for (int T = 1; ; ++T) {
        real cur = 0;
        for (int i = 1; i <= n; ++i)
            if (w[i])
                cur += max((real)i, E);
        cur /= t;
        // cout << cur << " " << E << endl;
        E = cur;
        if (ret < E - c * T)
            ret = E - c * T;
        else
            break;
    }
    return ret;
}

real f[N + 2];
int cb[N + 2][N + 2];

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cout << setprecision(20);
    real ans = 0;
    for (int i = 0; i <= N; ++i)
        for (int j = 0; j <= i; ++j)
            cb[i][j] = j ? cb[i - 1][j - 1] + cb[i - 1][j] : 1;
    
    for (int d = 4; d <= N; ++d) {
        f[1] = d;
        for (int i = 1; i < d; ++i)
            f[i + 1] = (f[i] - f[i - 1] * (d - i + 1) / d) * d / (i + 1);
        for (int i = 1; i <= d; ++i)
            f[i] /= cb[d][i];

        for (int c = 0; c <= N; ++c) {
            real cur = 0;
            for (int S = 1; S < (1 << d); ++S) {
                int t = __builtin_popcount(S);
                cur += f[t] * R(S, c);
            }
            cout << d << " " << c << " " << cur << endl;
            ans += cur;
        }
    }
    cout << ans << endl;

    return 0; 
}
