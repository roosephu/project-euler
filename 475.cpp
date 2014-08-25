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

const int n = 600, N = n / 3 + 10, MOD = 1e9 + 7;

int f[N][N][N];                 // 3, 2, 1
int64 cb[N][N], fac[N];

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    f[n / 3][0][0] = 1;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= i; ++j)
            cb[i][j] = j ? (cb[i - 1][j - 1] + cb[i - 1][j]) % MOD : 1;
    fac[0] = 1;
    for (int i = 1; i < N; ++i)
        fac[i] = fac[i - 1] * i % MOD;
    
    for (int i = n / 3; i >= 0; --i)
        for (int j = n / 3; j >= 0; --j)
            for (int k = n / 3; k >= 0; --k)
                if (f[i][j][k])
                    for (int a = 0; a <= 4 && a <= i; ++a)
                        for (int b = 0; a + b <= 4 && b <= j; ++b) {
                            int c = 4 - a - b;
                            if (c > k) continue;
                            int64 x = cb[j][b] % MOD * cb[k][c] % MOD * fac[b] % MOD * fac[c] % MOD * cb[4][a] % MOD * cb[4 - a][b] % MOD;
                            (f[i - a][j - b + a][k - c + b] += f[i][j][k] * x % MOD) %= MOD;
                        }

    int64 ans = f[0][0][0];
    // for (int i = 1; i <= n / 3; ++i)
    //     ans = ans * fpm(i, MOD - 2, MOD) % MOD;
    cout << ans << endl;

    return 0; 
}
