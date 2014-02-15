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

const int64 N = 1e17, L = sqrt(N);

// int prime[L + 1], lnk[L + 1];
int *prime, *lnk;
int fac[20], top;
int cnt; int64 j, ans;
// vector<pair<int, int>> G[900];

void dfs(int t, int dep) {
    if (dep == 0) {
        int64 p = j * j * 5 / t + t - 4 * j, b = p + 4 * j - 2 * t, c = p - j;
        // if (b >= p * 2) {
        //     cerr << "err: " << j << " " << t << endl;
        // }
        // if (b >= 2 * p) {
        //     cerr << "err: " << j << " " << t << endl;
        //     return ;
        // }
        if (b * c > N) return ;
        ans += N / b / c;
        // assert(gcd(b, c) == 1 && b < 2 * p && c > 0 && p * p * 5 == b * b + c * c * 4);
        // cerr << b << " " << c << " " << p << " " << b * c << " " << cnt << endl;
        ++cnt;
        if (cnt % 1000000 == 1) cerr << cnt << endl;
        return ;
    }

    dfs(t, dep - 1);
    if (j / t >= fac[dep]) dfs(t * fac[dep], dep - 1);
}

// conclusion: 1/b^2 + 1/c^2 = 5/4a^2
int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    prime = new int[L + 1];
    lnk = new int[L + 1];
    FOR (i, 2, L) {
        if (!prime[i]) prime[++prime[0]] = i, lnk[i] = i;
        for (int j = 1, t, k = L / i; prime[j] <= k; ++j) {
            prime[t = prime[j] * i] = 1, lnk[t] = prime[j];
            if (i % prime[j] == 0) break;
        }
    }

    FOR (j, 2, L) {
        if (j & 1) continue;
        top = 0;

        bool u5 = 0;
        for (int x = j; x != 1; ) {
            int y = x; int64 s = 1;
            for (; lnk[y] == lnk[x]; x /= lnk[x])
                s *= lnk[x];
            s *= s;
            if (lnk[y] == 5) s *= 5, u5 = 1;
            if (s <= j) fac[++top] = s;
        }
        if (!u5) fac[++top] = 5;

        ::j = j;
        dfs(1, top);
        // FOR (t, 1, j - 1) {
        //     if (j * j * 5 % t == 0) {
        //         int p = j * j * 5 / t + t - 4 * j, b = p + 4 * j - 2 * t, c = p - j;
        //         // if (b >= p * 2) {
        //         //     cerr << "err: " << j << " " << t << endl;
        //         // }
        //         assert((gcd(b, c) == 1) == (gcd(j * j * 5 / t, t) == 1));
        //         if (gcd(b, c) != 1 || b >= 2 * p) continue;
        //         cerr << b << " " << c << " " << p << " " << endl;
        //         ++cnt;
        //     }
        // }
    }

    // FOR (j, 1, L) {
    //     FOR (i, 1, 2 * j - 1) {
    //         int s = i * i + j * j, t = 2 * j - i;
    //         if (s % t == 0) {
    //             int p = s / t, b = p + 2 * i, c = p - j;
    //             if (gcd(b, c) != 1 || c <= 0 || b >= p * 2) continue;
    //             cerr << b << " " << c << " " << p << endl;
    //             ++cnt;
    //         }
    //     }
    // }

    // FOR (_, 1, sqrt(N)) {
    //     int i = _ * 2 - 1;
    //     FOR (__, 1, sqrt(N)) {
    //         int j = __ * 2 - 1;
    //         if (gcd(i, j) == 1) {
    //             int s = i * i + 4 * j * j;
    //             if (s % 5 != 0) continue;
    //             s /= 5;
    //             int p = sqrt(s);
    //             if (p * p != s || p >= i || p >= 2 * j) continue;
    //             cout << i << " " << j << " " << p << " " << i * j << " " << p * i << " " << 2 * p * j << endl;
    //             ans += N / i / j;
    //             cnt += 1;

    //             int64 A = i * (j - 1)
    //         }
    //     }
    // }
    
    // FOR (i, 3, sqrt(N) * 2) {
    //     FOR (j, (i + 1) / 2, i) {
    //         if ((int64)i * j > 2 * N) break;
    //         if (gcd(i, j) == 1) {
    //             int x = i * i + j * j;
    //             if (x % 5 != 0) continue;
    //             x /= 5;
    //             int y = sqrt(x);
    //             if (y * y != x) continue;
    //             cerr << i << " " << j << " " << y << " " << (2ll * y - i) * (2ll * y + i) << " " << (j - y) * (j + y) << endl;
    //             ans += 2 * N / i / j;
    //             ++cnt;
    //             // ans ++;
    //         }
    //     }
    // }

    
    // FOR (i, 1, 20) {
    //     FOR (j, i + 1, 20) {
    //         G[i * i + j * j].push_back(make_pair(i, j));
    //     }
    // }
    // FOR (i, 1, 800) {
    //     if (SZ(G[i]) == 2) {
    //         cerr << i << " ";
    //         for (auto x : G[i]) {
    //             cerr << "(" << x.car << ", " << x.cdr << ")";
    //         }
    //         cerr << endl;
    //     }
    // }

    cerr << ans << " " << cnt << endl;
    
    return 0; 
}
