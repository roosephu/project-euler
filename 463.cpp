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

const int64 n = 450283905890997363ll;
const int MOD = 1e9;

// int f[N];
map<int64, uint> F, G;

int64 calc(int64 x) {
    for (; ~x & 1; x >>= 1);
    if (F.count(x)) return F[x];
    int64 t = 0;
    if (x & 2)
        t = 3 * calc(x >> 1    ) - 2 * calc(x >> 2);
    else
        t = 2 * calc(x >> 1 | 1) -     calc(x >> 2);
    return F[x] = (t % MOD + MOD) % MOD;
}

int64 S(int64 x) {
    if (G.count(x)) return G[x];
    int64 t = 0;
    if (~x & 3)
        t = calc(x) + S(x - 1);
    else
        t += 6 * S(x >> 1) - 8 * S(x >> 2) - 1;
    return G[x] = (t % MOD + MOD) % MOD;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    // f[1] = f[2] = 1, f[3] = 3;
    // for (int i = 4; i <= n + 2; ++i) {
    //     if (i & 1) {
    //         if (i & 2)
    //             f[i] = 3 * f[i >> 1    ] - 2 * f[i >> 2];
    //         else
    //             f[i] = 2 * f[i >> 1 | 1] -     f[i >> 2];
    //     } else
    //         f[i] = f[i >> 1];
    // }
    // for (int i = 1; i <= n; i *= 2) {
    //     int64 s = 0;
    //     for (int j = 1; j <= i; ++j)
    //         s += f[j];
    //     cout << s << endl;
    // }
    F[1] = 1, F[3] = 3;
    for (int i = 1, s = 0; i <= 33; ++i)
        G[i] = s += calc(i);

    cout << S(n) << endl;
    // cout << S(63) << endl
    //      << S(31) << " " << S(15) << endl;
    // int64 x = 0;
    // for (int i = 1; i <= 1000000; ++i) {
    //     // (x += calc(i)) %= MOD;
    //     if (i >= 1e5) cout << x << endl;
    //     if (x != S(i)) {
    //         cout << i << " " << x << " " << S(i) << " " << S(31) << " " << S(15) << endl;
    //         break;
    //     }
    // }
    // for (int i = 1; i <= 1000; i += i)
    //     cout << S(i) << endl;
    cout << SZ(F) << " " << SZ(G) << endl;

    return 0; 
}
