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

const int N = 5, M = 18, MOD = 1e9;

typedef int64 mat[M][M];

mat f, U;

void matmul(mat a, mat b, mat c) {
    mat t;
    memset(t, 0, sizeof(t));
    FOR (i, 0, M) FOR (j, 0, M) FOR (k, 0, M)
        (t[i][j] += a[i][k] * b[k][j]) %= MOD;
    memcpy(c, t, sizeof(t));
}

int calc(int64 e) {
    memset(f, 0, sizeof(f)), f[17][17] = 1;
    memset(U, 0, sizeof(U));
    FOR (i, 0, 8) {
        U[i +  1][i +  0] = 1;
        U[i + 10][i +  9] = 1;
    }
    FOR (i, 9, 18) U[i][17] = 1;
    FOR (i, 9, 18) U[i][ 8] = 18 - i;
    FOR (i, 0,  9) U[i][ 8] = 10;

    for (; e; e >>= 1, matmul(U, U, U))
        e & 1 ? matmul(f, U, f), 0 : 0;
    return f[17][8];
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    // f[0] = 0, g[0] = 1;
    // FOR (i, 1, n + 1) {
    //     FOR (j, 1, 9) {
    //         if (i >= j) {
    //             f[i] += f[i - j] * 10 + g[i - j] * j;
    //             g[i] += g[i - j];
    //         }
    //     }
    // }
    int64 e = 1, ans = 0;
    FOR (i, 0, 17) {
        ans += calc(e *= 13);
    }
    cout << ans % MOD << endl;

    return 0; 
}
