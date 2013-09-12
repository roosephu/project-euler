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

const int L2 = 20, L3 = 13, N = 1000000 + 1;

int f[N][L2][L3], g[N];
int P2[L2], P3[L3];

bool isP(int x) {
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0) return false;
    return true;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    FOR (i, 0, L2) P2[i] = 1 << i;
    FOR (i, 0, L3) P3[i] = i ? P3[i - 1] * 3 : 1;

    FOR (j, 0, L2) {
        FOR (k, 0, L3) {
            int p = P2[j] * P3[k];
            if (p >= N) break;
            f[p][j][k] = 1;
        }
    }
    FOR (i, 1, N) {
        FOR (j, 0, L2) {
            FOR (k, 0, L3) {
                if (!f[i][j][k]) continue;
                g[i] += f[i][j][k];
                FOR (u, 0, j) {
                    FOR (v, k + 1, L3) {
                        int q = i + P2[u] * P3[v];
                        if (q >= N) break;
                        f[q][u][v] += f[i][j][k];
                    }
                }
            }
        }
    }
    int64 ans = 0;
    FOR (i, 2, N) {
        if (g[i] == 1 && isP(i))
            ans += i;
    }
    cerr << ans << endl;

    return 0; 
}
