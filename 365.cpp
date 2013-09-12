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

const int L = 1001, U = 5000;
const int64 N = 1e18, M = 1e9;

int fac[U], ifac[U], ret[U], p, P[U];

int lucas(int64 n, int64 m, int p) {
    if (n == 0 && m == 0) return 1;
    int a = n % p, b = m % p;
    if (a < b) return 0;
    return fac[a] * ifac[b] % p * ifac[a - b] % p * lucas(n / p, m / p, p) % p;
}

bool isP(int x) {
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0) return false;
    return x != 1;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    int top = 0;
    FOR (p, L, U) {
        if (!isP(p)) continue;

        ::p = p;
        P[++top] = p;
        fac[0] = 1;
        FOR (i, 1, p) fac[i] = fac[i - 1] * i % p;
        ifac[p - 1] = fpm(fac[p - 1], p - 2, p);
        ROF (i, p - 1, -1) ifac[i - 1] = ifac[i] * i % p;

        ret[top] = lucas(N, M, p);
    }

    int64 ans = 0;
    FOR (i, 1, top) {
        FOR (j, i + 1, top) {
            FOR (k, j + 1, top + 1) {
                if (!ret[i] && !ret[j] && !ret[k]) continue;
                int64 prod = 1ll * P[i] * P[j] * P[k];
                int64 cur =
                    fpm(P[j] * P[k], P[i] - 2, P[i]) * P[j] * P[k] * ret[i] +
                    fpm(P[k] * P[i], P[j] - 2, P[j]) * P[k] * P[i] * ret[j] +
                    fpm(P[i] * P[j], P[k] - 2, P[k]) * P[i] * P[j] * ret[k];

                ans += cur % prod;
            }
        }
    }
    cerr << ans << endl;

    return 0; 
}
