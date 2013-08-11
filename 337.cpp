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

const int N = 2e7, MOD = 1e8;
int bit[N + 1], phi[N + 1], prime[N + 1], f[N + 1];

struct zp {
    int x;

    operator int() { return x; }
    operator int64() { return x; }
    zp() : x(0) {}
    zp(int _) : x(_ % MOD) {}
    
    int operator + (int a) {
        x += a;
        if (x >= MOD) x -= MOD;
        return x;
    }

    int operator - (int a) {
        x -= a;
        if (x < 0) x += MOD;
        return x;
    }

    int operator * (int a) {
        x = (int64)x * a % MOD;
        return a;
    }

    int operator / (int a) {
        x = x * fpm(a, MOD - 2, MOD) % MOD;
        return x;
    }
};

void bit_modify(int x, int v) {
    for (; x <= N; x += x & -x) (bit[x] += v) %= MOD;
}

int bit_query(int x) {
    int t = bit[x];
    for (; x &= x - 1; (t += bit[x]) %= MOD);
    return t;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    phi[1] = 1;
    FOR (i, 2, N + 1) {
        if (!prime[i]) prime[++prime[0]] = i, phi[i] = i - 1;
        for (int j = 1, k = N / i, t; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = 1;
            if (i % prime[j]) phi[t] = phi[i] * phi[prime[j]];
            else {phi[t] = phi[i] * prime[j]; break; }
        }
    }

    int64 ans = 0;
    f[6] = 1;
    FOR (i, 6, N + 1) {
        (f[i] += bit_query(phi[i])) %= MOD;
        ans += f[i];
        bit_modify(phi[i] + 1, f[i]);
        bit_modify(    i     , MOD - f[i]);
    }
    cerr << ans % MOD << endl;

    return 0; 
}
