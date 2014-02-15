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

const int n = 2e7, N = n + 10;

int prime[N], lnk[N], top, phi[N];
int fac[30];
int64 wt[30];
int now, nn, lmt;

int64 inv(int m, int t) {
    // if (t == 1) return 1;
    // return (m - m / t) * inv(m, m % t) % m;
    return fpm(t, phi[m] - 1, m);
}

void dfs(int lv, int s) {
    if (lv == 0) {
        if (s != lmt && s > now && (int64)s * s % nn == 1)
            now = s;
        return ;
    }
    int k = fac[lv];
    dfs(lv - 1, (wt[lv] *      1  + s) % nn);
    if (k != 2)
        dfs(lv - 1, (wt[lv] * (k - 1) + s) % nn);
    if (k != 2 && (k & 1) == 0) {
        dfs(lv - 1, (wt[lv] * (k / 2 - 1) + s) % nn);
        dfs(lv - 1, (wt[lv] * (k / 2 + 1) + s) % nn);
    }
}

int Find(int x) {
    for (int i = x - 2; i; --i)
        if (i * i % x == 1)
            return i;
    return 0;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    int64 ans = 0;

    for (int i = 2; i <= n; ++i) {
        if (!prime[i]) prime[++prime[0]] = i, lnk[i] = 1;
        for (int j = 1, k = n / i, t; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = 1;
            if (i % prime[j]) lnk[t] = i;
            else {lnk[t] = lnk[i]; break; }
        }
    }
    for (int i = 1; i <= prime[0]; ++i) {
        for (int64 j = prime[i]; j <= n; j *= prime[i])
            phi[j] = j / prime[i] * (prime[i] - 1);
    }

    for (int i = 3; i <= n; ++i) {
        lmt = i - 1;
        nn = i;
        top = 0;
        now = 0;
        for (int x = nn; x != 1; x = lnk[x]) {
            int f = x / lnk[x];
            fac[++top] = f;
            wt[top] = inv(f, (nn / f) % f) * (nn / f) % nn;
            // assert(wt[top] % lnk[x] == 0);
        }

        dfs(top, 0);
        // cerr << i << " " << now << " " << Find(i) << endl;
        ans += now;
    }
    cout << ans << endl;

    return 0; 
}
