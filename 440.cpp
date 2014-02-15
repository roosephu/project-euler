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

const int MOD = 987898789, N = 2200;

struct matrix {
    int64 x[2][2];

    int64 *operator[](const size_t t) {return x[t]; };
} ;

matrix operator * (matrix a, matrix b) {
    matrix t; memset(&t, 0, sizeof(t));
    FOR (i, 0, 1) FOR (j, 0, 1) FOR (k, 0, 1)
        (t[i][j] += a[i][k] * b[k][j]) %= MOD;
    return t;
}

matrix operator ^ (matrix a, int e) {
    matrix u = a; --e;
    for (; e; a = a * a, e >>= 1)
        e & 1 ? u = u * a, 0 : 0;
    return u;
}

int64 f[N];
matrix x, y;

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    int single = 0, n = 2000;
    FOR (i, 1, n) {
        FOR (j, 1, n) {
            int x = gcd(i, j);
            if ((i / x) % 2 == 1 && (j / x) % 2 == 1)
                ++f[x];
            else
                ++single;
        }
    }

    int64 ans = 0;
    FOR (i, 1, n) {
        cout << i << endl;
        x[0][0] = 0, x[0][1] = 1;
        y[0][0] = 0, y[0][1] = 1;
        y[1][0] = 1, y[1][1] = 10;

        FOR (j, 1, n) {
            y = y^i;
            ans += f[j] * y[1][1];
        }
        if (i & 1)
            ans += single * 10;
        else
            ans += single;
    }
    cout << ans % MOD << endl;

    return 0; 
}

