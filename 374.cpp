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

const int MOD = 982451653, LMT = 2e7;
const int64 N = 1e14;

int inv[LMT];

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    inv[1] = 1;
    FOR (i, 2, LMT) inv[i] = (int64)inv[MOD % i] * (MOD - MOD / i) % MOD;

    int64 fac = 1, ans = 0, sinv = 0;
    FOR (i, 2, LMT) {
        int64 L = i * (i - 1ll) / 2, R = i * (i + 1ll) / 2 - 1; // [L, R]
        fac = fac * i % MOD;
        if (R <= N) ans += fac * (i - 1) % MOD; // R
        if (R == 2) ans += 1;
        else if (R - 1 <= N) ans += fac * inv[2] % MOD * inv[i] % MOD * (i + 1) % MOD * (i - 2) % MOD;         // R - 1
        if (R - 2 <= N) {
            ans += sinv * fac % MOD * (i - 2) % MOD;
        } else {
            int x = i - 1;
            for (; L <= N; ++L) {
                ans += fac * inv[x] % MOD * (i - 2) % MOD;
                --x;
            }
        }
        sinv = (sinv + inv[i]) % MOD;
        if (R > N) break;
    }
    cerr << ans % MOD << endl;

    return 0; 
}
