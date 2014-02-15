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

const int n = 1000, N = 1100;

real func(real x, int t) {
    return pow(1 - x, t) * pow(1 + 2 * x, n - t) - 1e9;
}

int find(int t) {
    // real L = 0, R = 1, m;
    // for (; (m = (L + R) / 2), R - L > 1e-18; )
    //     func(m, t) < 0 ? (L = m) : (R = m);
    // cout << setprecision(20) << L << " " << m << " " << R << " " << func(R, t) << endl;
    return func(1 - 3 * t / ((real)2 * n), t) >= 0;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    real ans = 0, cb = 1;
    cout << setprecision(20);
    for (int i = 0; i <= n; ++i) {
        real v = func(1 - 3 * i / ((real)2 * n), i);
        cout << i << " " << v << endl;
        if (v < 1e9) break;
        cb *= (n - i) / (i + (real)1);
        ans += cb;
    }
    cout << setprecision(20) << ans / pow((real)2, n) << endl;

    return 0; 
}
