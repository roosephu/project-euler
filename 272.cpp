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
#include <gmpxx.h>
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
#define fst first
#define snd second
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

typedef mpz_class ZZ;
// typedef int64 ZZ;

const int n = 2e7, N = n + 10, stop = 1100;

int prime[N];
int lo[21];
ZZ o[N], P[1000000];

void init() {
    int i, j, k, t;
    for (i = 2; i <= n; ++i) {
        if (!prime[i]) prime[++prime[0]] = i, o[i] = i % 3 == 2;
        for (j = 1, k = n / i; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = 1, o[t] = o[i] && o[prime[j]];
            if (i % prime[j] == 0) break;
        }
    }
}

map<int64, ZZ> f[6];

ZZ calc(int64 n, bool b) {
    for (int i = 0; i <= 5; ++i)
        f[i].clear();
    f[0][(int64)n] = 1;
    if (b) {
        int64 m = n / 3; ZZ v = 3;
        for (; m /= 3, v *= 3, m; )
            f[1][m] += v;
    }
    
    for (int i = 2; i <= stop; ++i)
        for (int j = 4; j >= 0; --j)
            for (auto x : f[j]) {
                auto p = x.snd;
                for (auto v = x.fst; v /= prime[i], p *= prime[i], v; )
                    f[j + 1][v] += p;
            }
    for (int i = 0; i <= 5; ++i)
        cout << i << "  " << SZ(f[i]) << endl;

    ZZ ans = 0;
    for (auto x : f[5]) {
        ans += o[x.fst] * x.snd;
    }
    cout << ans << endl;
    
    for (auto x : f[4]) {
        int cur = stop + 1;
        for (; cur <= prime[0] && x.fst >= prime[cur]; ) {
            int nxt = lower_bound(prime + cur, prime + prime[0] + 1, x.fst / (x.fst / prime[cur]) + 1) - prime;
            ans += o[x.fst / prime[cur]] * x.snd * (P[nxt - 1] - P[cur - 1]);
            cur = nxt;
        }
    }
    cout << ans << endl;
    return ans;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    init();
    int top = prime[0]; prime[0] = 0;
    for (int i = 1; i <= top; ++i) {
        if (prime[i] % 3 < 2) {
            prime[++prime[0]] = prime[i];
        }
    }

    o[1] = 1;
    for (int i = 1; i <= n; ++i)
        o[i] = o[i - 1] + o[i] * i;
    for (int i = 1; i <= prime[0]; ++i)
        P[i] = P[i - 1] + prime[i];

    int64 n = 1e11;
    ZZ ans = calc(n, true) + 3 * calc(n / 3, false);
    cout << ans << endl;

    return 0; 
}

