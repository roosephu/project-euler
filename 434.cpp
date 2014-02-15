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
#ifdef DEBUG
#define cvar(x) cerr << "<" << #x << ": " << x << ">"
#define evar(x) cvar (x) << endl
template<class T> void DISP(const char *s, T x, int n) {cerr << "[" << s << ": "; for (int i = 0; i < n; ++i) cerr << x[i] << " "; cerr << "]" << endl;}
#define disp(x,n) DISP(#x " to " #n, x, n)
#else
#define cvar(...) ({})
#define evar(...) ({})
#define disp(...) ({})
#endif
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
    Graph(int n) {adj.clear (); adj.resize (n + 5);}
    Graph() {adj.clear (); }
    void resize(int n) {adj.resize (n + 5); }
    void add(int s, edge e){adj[s].push_back (e);}
    void del(int s, edge e) {adj[s].erase (find (iter (adj[s]), e)); }
    vector<edge>& operator [](int t) {return adj[t];}
};

const int N = 110, MOD = 1000000033;
int n = 100, m = 100;

int w[6][6];
int ufs[11];
int cnt, ans;
int64 f[N + 1][N + 1], cb[N + 1][N + 1], tab[N * N + 1];

// int find(int t) {
//     return ufs[t] ? ufs[t] = find(ufs[t]) : t;
// }

// void update() {
//     int cnt = n + m - 1;
//     memset(ufs, 0, sizeof(ufs));
//     FOR (i, 1, n) {
//         FOR (j, 1, m) {
//             if (w[i][j]) {
//                 int x = find(i), y = find(n + j);
//                 if (x != y) ufs[x] = y, --cnt;
//                 if (!cnt) break;
//             }
//         }
//     }
//     ans += !cnt;
// }

// void dfs(int i, int j) {
//     if (i > n) {
//         update();
//         return ;
//     }
//     w[i][j] = 0, dfs(i + (j == m), j % m + 1);
//     w[i][j] = 1, dfs(i + (j == m), j % m + 1);
// }

int main(int argc, char **argv) {
#ifndef ONLINE_JUDGE
    // freopen("434.in" , "r", stdin);
    // freopen("434.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);

    FOR (i, 0, N * N) tab[i] = i ? tab[i - 1] * 2 % MOD : 1;
    FOR (i, 0, N) {
        FOR (j, 0, i) {
            cb[i][j] = j ? (cb[i - 1][j - 1] + cb[i - 1][j]) % MOD : 1;
        }
    }
    
    FOR (n, 1, N) {
        FOR (m, 0, N) {
            if (m == 0) f[n][m] = n == 1;
            else {
                f[n][m] = tab[n * m];
                FOR (i, 1, n) {
                    FOR (j, 0, m) {
                        if (i != n || j != m)
                            (f[n][m] += MOD - cb[n - 1][i - 1] * cb[m][j] % MOD * f[i][j] % MOD * tab[(n - i) * (m - j)] % MOD) %= MOD;
                    }
                }
            }
        }
    }
    FOR (i, 1, n) {
        FOR (j, 1, n) {
            (ans += f[i][j]) %= MOD;
        }
    }
    
    // for (n = 1; n <= 5; ++n) {
    //     for (m = 1; m <= 5; ++m) 
    //         dfs(1, 1);
    // }
    cout << ans << endl;

    return 0; 
}
