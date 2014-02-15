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
template <typename T> T gcd(T x, T y) {for (T t; x; t = x, x = y % x, y = t); return y; }

template<class edge> struct Graph {
     vector<vector<edge> > adj;
     Graph(int n) {adj.clear (); adj.resize (n + 5);}
     Graph() {adj.clear (); }
     void resize(int n) {adj.resize (n + 5); }
     void add(int s, edge e){adj[s].push_back (e);}
     void del(int s, edge e) {adj[s].erase (find (iter (adj[s]), e)); }
     vector<edge>& operator [](int t) {return adj[t];}
};

const int N = 19;

int64 dp[2][1 << N][2], (*f)[2] = dp[0], (*g)[2] = dp[1];
int64 DP[2][43046721][2];

int64 calc(int d) {
    int mask = (1 << d) - 1;
    memset(f, 0, sizeof(dp[0]));
    f[0][0] = 1;
    for (int i = 0; i < d; ++i) {
        memset(g, 0, sizeof(dp[0]));
        for (int j = 0; j <= mask; ++j) {
            int64 s = 1;
            for (int x = 0; x < d; ++x)
                if (j >> x & 1)
                    s |= 1 << (x * 10 % d);
            for (int x = 0; x <= 9; ++x) {
                if (i == 0 && x == 0) continue;
                int y = x % d;
                (s = (s << y) | (s >> (d - y))) &= mask;
                if (s & 1) {
                    g[s][1] += f[j][0];
                } else {
                    g[s][0] += f[j][0];
                    g[s][1] += f[j][1];
                }
            }
        }
        swap(f, g);
    }
    
    int64 ret = 0;
    for (int s = 0; s <= mask; ++s)
        ret += f[s][1];
    cout << d << " " << ret << endl;
    return ret;
}

int64 calc2(int d, int m) {
    int64 (*f)[2] = DP[0], (*g)[2] = DP[1];
    
    memset(f, 0, sizeof(DP[0]));
    f[0][0] = 1;
    for (int i = 0; i < d; ++i) {
        memset(g, 0, sizeof(DP[0]));
        for (int j = 0; j <= mask; ++j) {
            int64 s = 1;
            for (int x = 0; x < m; ++x)
                if (j >> x & 1)
                    s |= 1 << (x * 10 % d);
            for (int x = 0; x <= 9; ++x) {
                if (i == 0 && x == 0) continue;
                int y = x % d;
                (s = (s << y) | (s >> (d - y))) &= mask;
                if (s & 1) {
                    g[s][1] += f[j][0];
                } else {
                    g[s][0] += f[j][0];
                    g[s][1] += f[j][1];
                }
            }
        }
        swap(f, g);
    }
    
    int64 ret = 0;
    for (int s = 0; s <= mask; ++s)
        ret += f[s][1];
    cout << d << " " << ret << endl;
    return ret;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    int64 ans = 0;
    for (int i = 1; i <= 7; ++i) {
        ans += calc(i);
    }
    cout << ans << endl;

    return 0; 
}
