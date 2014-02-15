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

const int MOD = 1234567891;

int64 ans = 0;
int x[200], y[200];
uint n = 1e9;

int64 cnt[100];
int inv[100];
int64 tab[100], fac[100];

void update(int t, int c = 1) {
    int64 d = 0, s = 0;
    for (int i = 1; i <= t; ++i)
        s += y[i]; // cout << "(" << x[i] << "," << y[i] << ")" << " ";
    // cout << endl;
    for (d = tab[s]; t; --t)
        (d = d * fac[y[t]]) %= MOD;
    // cout << d << " " << c << endl;
    ans += d * c % MOD;
}

void dfs(int t, int s, int k) {
    update(t);

    int l = n / s;
    if (k > l) return ;
    if ((int64)k * k > l) {
        y[t + 1] = 1;
        update(t + 1, l - k + 1);
        return ;
    }
    
    ++t;
    for (; k * k <= l; ++k) {
        x[t] = k;
        int ns = s, nl = l;
        for (y[t] = 1; k <= nl; ++y[t], nl /= k)
            dfs(t, ns *= k, k + 1);
    }

    if (k <= l) {
        int d = l - k + 1;
        y[t] = 1;
        update(t, d);
    }
}

int main(int argc, char **argv) {
#ifndef ONLINE_JUDGE
#endif
    ios_base::sync_with_stdio(false);

    tab[0] = fac[0] = 1;
    for (int i = 1; i < 100; ++i) {
        tab[i] = tab[i - 1] * (n + 1 - i) % MOD;
        fac[i] = fac[i - 1] * fpm(i, MOD - 2, MOD) % MOD;
        // cout << tab[i] << " " << fac[i] << endl;
    }
    dfs(0, 1, 2);
    cout << ans % MOD << endl;

    return 0; 
}
