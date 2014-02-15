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
template <typename T> T gcd(T x, T y) {
    for (T t; x; t = x, x = y % x, y = t)
        ;
    return y;
}

template<class edge> struct Graph {
    vector<vector<edge> > adj;
    Graph(int n) {adj.clear(); adj.resize(n + 5);}
    Graph() {adj.clear(); }
    void resize(int n) {adj.resize(n + 5); }
    void add(int s, edge e){adj[s].push_back(e);}
    void del(int s, edge e) {adj[s].erase(find(iter(adj[s]), e)); }
    vector<edge>& operator [](int t) {return adj[t];}
};

const int N = 65536;

int n;
real y[N + 2], dx;
bool in[N + 2];
real ans, cir, area;

bool update(int t, real v) {
    if (v < 0 || v > 1) return false;
    real c = cir, a = area;
    c += hypot(dx, y[t + 1] - v) - hypot(dx, y[t] - y[t + 1]);
    c += t ? (hypot(dx, y[t - 1] - v) - hypot(dx, y[t] - y[t - 1])) : (v - y[t]);
    a += (t ? dx : (dx / 2)) * (v - y[t]);
    if (a / c > ans) {
        ans = a / c;
        area = a;
        cir = c;
        return true;
    }
    return false;
}

void init() {
    cir = y[0], area = y[0];
    FOR (i, 0, n - 1) {
        real dy = y[i + 1] - y[i];
        cir += hypot(dx, dy);
        area += (n - i - 0.5) * dx * dy;
    }
}

void adjust(real eps) {
    int cnt = 0;
    queue<int> Q;
    FOR (i, 0, n - 1) Q.push(i), in[i] = true;

    for (; !Q.empty(); Q.pop(), ++cnt) {
        if ((cnt & 511) == 0) init();

        int t = Q.front(); in[t] = false;
        if (update(t, y[t] + eps)) y[t] += eps;
        else if (update(t, y[t] - eps)) y[t] -= eps;
        else continue;

        if (t - 1 >= 0 && !in[t - 1]) Q.push(t - 1), in[t - 1] = true;
        if (t + 1 <  n && !in[t + 1]) Q.push(t + 1), in[t + 1] = true;
    }
}

int main(int argc, char **argv) {
    freopen("314.out", "w", stdout);
    ios_base::sync_with_stdio(false);

    cerr << setprecision(15);

    y[1] = 1, n = 1;
    for (; n * 2 < N; ) {
        n *= 2;
        ROF (i, n, 0) {
            y[i * 2] = y[i];
        }
        for (int i = 1; i <= n; i += 2) {
            y[i] = (y[i + 1] + y[i - 1]) / 2;
        }
        
        dx = 1.0 / n;
        real eps = dx;
        init();

        ans = area / cir;
        FOR (i, 1, 200) {
            // cerr << ans << endl;
            eps /= 1.1;
            adjust(eps);
        }
        // cerr << ans * 250 << endl;
    }

    real hi = 0, lo = 1e300;
    cout << setprecision(20);
    cout << "ListPlot[{0,";
    FOR (i, 0, n) {
        y[i] /= dx;
        cout << y[i] << ",";
        if (0 < i && n - y[i] > 2) {
            real x = n / 4, d = hypot(i - n + x, y[i] - x);
            if (chkmax(hi, d)) {
                // cerr << hi << " " << i << endl;
            }
            if (chkmin(lo, d)) {
                // cerr << lo << " " << i << endl;
            }
        }
    }
    cout << "}, AspectRatio -> 1]" << endl;
    cerr << hi << " " << lo;
    

    return 0; 
}
