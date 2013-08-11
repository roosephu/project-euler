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

const int N = 1e8, M = 1e9, U = N;

int prime[U + 1], dvs[U + 1];

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    // int LMT = sqrt(U) + 1;
    FOR (i, 2, U + 1) {
        if (!prime[i])  prime[++prime[0]] = i, dvs[i] = 2;
        for (int j = 1, t, k = U / i; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = i;
            if (i % prime[j]) dvs[t] = dvs[i] * 2;
            else {dvs[t] = dvs[i]; break; }
        }
    }

    dvs[1] = 1;
    int64 ans = 0;
    FOR (i, 1, U + 1) {
        if (i & 1)
            ans += 2ll * dvs[i] * (N / i) * (M / i);
        else {
            ans += 2ll * dvs[i] * ((N / i / 2ll) * (M / i / 2) + ((M / i + 1ll) / 2) * ((N / i + 1ll) / 2));
        }
    }
    cout << ans << endl;

    return 0; 
}
