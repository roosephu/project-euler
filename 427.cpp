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

const int N = 7500000, MOD = 1e9 + 9; // 75000000

int fac[N + 1], caf[N + 1], PN[N + 1], QN[N + 1];

int64 cb(int n, int m) {
    return (int64)fac[n] * caf[m] % MOD * caf[n - m] % MOD;
}

int64 calc(int n, int k) {
    int64 ret = 0;
    FOR (i, 0, n / k) {
        int t = i * (k - 1);
        int64 v = PN[n - i * k] * cb(n - t, i) % MOD * QN[i] % MOD;
        if (i & 1) v = MOD - v;
        (ret += MOD + v) %= MOD;
    }
    return ret;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    fac[0] = 1;
    FOR (i, 1, N) fac[i] = (int64)fac[i - 1] * i % MOD;
    caf[N] = fpm(fac[N], MOD - 2, MOD);
    ROF (i, N, 1) caf[i - 1] = (int64)caf[i] * i % MOD;
    PN[0] = 1, QN[0] = 1;
    FOR (i, 1, N) PN[i] = (int64)PN[i - 1] * N % MOD, QN[i] = (int64)QN[i - 1] * (N - 1) % MOD;

    int64 ans = 0;
    FOR (k, 1, N) {
        int64 now = calc(N, k) - calc(N - k, k) + MOD;
        now = (fpm(N, N, MOD) + MOD - now) % MOD;
        ans += now;
        if (k < 100 || k % 10000 == 1) cout << k << endl;
        // cout << now << " " << ans << endl;
    }
    cout << (ans % MOD + MOD) % MOD << endl;

    return 0; 
}

