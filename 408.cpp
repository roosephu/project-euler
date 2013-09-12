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

const int N = 10000000, MOD = 1000000007, T = 10000;

int fac[N * 2 + 1], ifac[N + 1];
int X[T], Y[T], f[T], top;

int cb(int a, int b) {
    if (a < 0 || b < 0) return 0;
    return (int64)fac[a + b] * ifac[a] % MOD * ifac[b] % MOD;
}

int calc(int x, int y) {
    int64 t = cb(x, y);
    FOR (i, 0, top) {
        t += MOD - (int64)cb(x - X[i], y - Y[i]) * f[i] % MOD;
    }
    return t % MOD;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    fac[0] = 1;
    FOR (i, 1, N * 2 + 1) fac[i] = (int64)fac[i - 1] * i % MOD;
    ifac[N] = fpm(fac[N], MOD - 2, MOD);
    ROF (i, N, -1) ifac[i - 1] = (int64)ifac[i] * i % MOD;
    
    FOR (x, 1, N) {
        if (x * x > N) break;
        FOR (y, 1, N) {
            int s = x * x + y * y;
            if (y * y > N) break;
            if (sqr(int(sqrt(s))) == s) {
                X[top] = x * x;
                Y[top] = y * y;
                f[top] = calc(x * x, y * y);
                top++;
                // cerr << x * x << " " << y * y << endl;
            }
        }
    }
    cerr << calc(N, N) << endl;

    return 0; 
}
