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

const int N = 1e4;

int Prime[N + 1], lnk[N + 1], P[N + 1];
bool B[N + 1];

void update(int p, int g) {
    if (B[p] || g > p) return ;
    for (int b = p - 1; b != 1; b = lnk[b])
        if (fpm(g, p / P[b], p) == 1) return ;
    B[p] = g;
    // cerr << p << " " << g << endl;
}

#include <pari/pari.h>

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    FOR (i, 2, N) {
        if (!Prime[i]) Prime[++Prime[0]] = i, lnk[i] = 1, P[i] = i;
        for (int j = 1, k = N / i, t; Prime[j] <= k; ++j) {
            Prime[t = i * Prime[j]] = 1, P[t] = Prime[j];
            if (i % Prime[j]) lnk[t] = i;
            else {lnk[t] = lnk[i]; break; }
        }
    }

    Prime[Prime[0] + 1] = 1e9;
    pari_init(1 << 24, 100000000);
    // allocatemem(1 << 20);

    FOR (k, 3, N) {
        if (k % 100000 == 1) cerr << k << endl;
        int64 x = k * (k - 1ll) - 1;
        // if (uisprime(x)) {
        //     if (x <= N) update(x, k);
        //     continue;
        // }
        GEN z = factoru(x), T = gel(z, 1);
        FOR (i, 1, glength(T)) {
            int64 p = (long)gel(T, i);
            if (p <= N) update(p, k);
        }
        cgiv(z);

        // for (int *p = Prime + 1; (int64)*p * *p <= x && x > N; ++p) {
        //     if (x % *p == 0) {
        //         update(*p, k);
        //         for (; x /= *p, x % *p == 0; );
        //     }
        // }
        // for (; x != 1 && x <= N; x = lnk[x]) update(P[x], k);
    }

    int64 ans = 0, t = 0;
    FOR (i, 1, Prime[0]) {
        int x = Prime[i];
        if (!B[x]) continue;
        ans += x, ++t;
        cerr << x << endl;
    }
    cerr << "ans: " << ans << " " << t << endl;

    return 0; 
}

