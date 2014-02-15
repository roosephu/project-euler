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

const int MOD = 1953125, n = 1e6, PHI = MOD - MOD / 5, N = 1e6 + 10;

set<int> V[MOD + 1], U[513];
int P[MOD];

int phi(int x) {
    int y = x;
    if (x % 2 == 0) y /= 2;
    if (x % 5 == 0) y = y / 5 * 4;
    return y;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    P[0] = 1;
    for (int i = 1; i <= PHI; ++i)
        P[i] = P[i - 1] * 2 % MOD;
    for (int x = 2, e = 1; x != 1; x = x * 2 % MOD, ++e) {
        for (int j = 0; j < 5; ++j, x += MOD) {
            int y = gcd(x, PHI);
            if (e % y != 0) continue;
            int ee = e / y, xx = x / y, pp = PHI / y;
            int b = fpm(xx, phi(pp) - 1, pp) * ee % pp;
            for (int i = 0; i < y; b += pp, ++i)                // all possible solutions
                V[P[b]].insert(x);
        }
    }
    for (int i = 0; i <= 512; ++i) {
        for (int j = 0; j <= 512; ++j) {
            if (fpm(i, j, 512) == j % MOD)
                U[i].insert(j);
        }
    }
    for (int i = 1; i <= MOD; ++i)
        for (int j = 0; j <= 9; ++j)
            for (int k = 0; k < 4; ++k)
                if (fpm(i, j + k * MOD, MOD) == j)
                    V[i].insert(j + k * MOD);
    for (int i = 0; i <= 512; ++i)
        if (i % 2 == 0)
            U[i].insert(0);
    for (int i = 0; i <= MOD; ++i)
        if (i % 5 == 0)
            V[i].insert(0);

    int64 ans = 0;
    for (int i = 2; i <= 1e6; ++i) {
        
        int f = 0;
        for (auto &x : U[(i - 1) % 512 + 1]) {
            for (auto &y : V[(i - 1) % MOD + 1]) {
                int k = (x * 212890625ll + y * 787109376ll) % int(1e9);
                if (fpm(i, k, 1e9) == k) chkmax(f, k);
            }
        }
        // if (f) {
        if (i % 1000 == 0)
            cout << i << " " << f << endl;
        //     assert(fpm(i, f, 1e9) == f);
        // }
        ans += f;
    }
    cout << ans << endl;
    
    return 0; 
}

