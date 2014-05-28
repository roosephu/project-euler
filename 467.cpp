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

#define inf 0x3F3F3F3F
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

const int LMT = 1e6, n = 10000, N = n + 2, MOD = 1e9 + 7;

int prime[LMT + 1], S[N], T[N];
short f[N][N];

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    for (int i = 2; i <= LMT; ++i) {
        if (!prime[i]) prime[++prime[0]] = i;
        for (int j = 1, k = LMT / i, t; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    
    int a = n, b = n, p = 1;
    for (int i = 2; a || b; ++i) {
        int x = i - (i - 1) / 9 * 9;
        if (i == prime[p]) {
            if (a) {
                --a;
                S[a] = x;
            }
            ++p;
        } else if (b) {
            --b;
            T[b] = x;
        }
    }
    for (int i = 0; i < n; ++i)
        printf("%d", S[i]);
    puts("");
    for (int i = 0; i < n; ++i)
        printf("%d", T[i]);
    puts("");

    memset(f, 0x3F, sizeof(f));
    f[0][0] = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            short x = f[i][j] + 1;
            if (i < n) chkmin(f[i + 1][j], x);
            if (j < n) chkmin(f[i][j + 1], x);
            if (i < n && j < n && S[i] == T[j])
                chkmin(f[i + 1][j + 1], x);
        }
    }

    int64 ans = 0, cur = 1, cnt = 0;
    for (int i = n, j = n; i > 0 || j > 0; ) {
        int a = i > 0 ? S[i - 1] : 0, b = j > 0 ? T[j - 1] : 0, x;
        if (i == 0) x = b;
        else if (j == 0) x = a;
        else if (i && j) {
            if (a == b) x = a;
            else if (a < b) {
                if (f[i - 1][j] + 1 == f[i][j]) 
                    x = a;
                else
                    x = b;
            } else {
                if (f[i][j - 1] + 1 == f[i][j]) 
                    x = b;
                else
                    x = a;
            }
        }
        if (x == a && i > 0) --i;
        if (x == b && j > 0) --j;
        // ans += cur * x % MOD;
        // cur = cur * 10 % MOD;
        (ans = ans * 10 + x) %= MOD;
        printf("%d", x);
        ++cnt;
    }
    printf("\n%lld %lld %d\n", ans % MOD, cnt, (int)f[n][n]);
    
    return 0; 
}

