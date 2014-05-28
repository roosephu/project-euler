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

template<class edge> struct Graph
{
    vector<vector<edge> > adj;
    Graph(int n) {adj.clear (); adj.resize (n + 5);}
    Graph() {adj.clear (); }
    void resize(int n) {adj.resize (n + 5); }
    void add(int s, edge e){adj[s].push_back (e);}
    void del(int s, edge e) {adj[s].erase (find (iter (adj[s]), e)); }
    vector<edge>& operator [](int t) {return adj[t];}
};

const int MOD = 1000000000, LMT = 100000000;

int P[] = {2, 3, 5, 7, 11, 13, 17};
map<int64, int> f;
int prime[LMT], phi[LMT];

int prephi(int64 n)
{
    if (n < LMT) return phi[n];
    if (f.count(n)) return f[n];
    int &t = f[n];
    if (n & 1) t = ((n + 1) / 2 % MOD) * (n % MOD) % MOD;
    else t = (n / 2 % MOD) * ((n + 1) % MOD) % MOD;
    for (int64 i = 2, j; i <= n; i = j) {
        j = n / (n / i) + 1;
        (t += MOD - (j - i) % MOD * prephi(n / i) % MOD) %= MOD;
    }
    // cerr << n << " " << t << endl;
    return t;
}

int dfs(int d, int64 n)
{
    if (d == 7) return prephi(n);
    if (n == 0) return 0;
    int p = P[d];
    return ((p - 1ll) * dfs(d + 1, n) + dfs(d, n / p)) % MOD;
}

int main(int argc, char **argv)
{
#ifndef ONLINE_JUDGE
#endif
    ios_base::sync_with_stdio(false);

    FOR (i, 2, LMT - 1) {
        if (!prime[i]) prime[++prime[0]] = i, phi[i] = i - 1;
        for (int j = 1, k = (LMT - 1) / i, t; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = 1;
            if (i % prime[j]) phi[t] = phi[i] * phi[prime[j]];
            else {phi[t] = phi[i] * prime[j]; break; }
        }
    }
    phi[1] = 1;
    FOR (i, 1, LMT - 1) (phi[i] += phi[i - 1]) %= MOD;

    // cout << prephi(100) << endl;
    // int ans = 0;
    // FOR (i, 1, 5) {
    // 	ans += phi[i * 2] - phi[i * 2 - 1];
    // }
    cout << dfs(0, 1e11) << endl;
    // cout << ans << endl;

    cerr << 1.0 * clock() / CLOCKS_PER_SEC << endl;
    return 0; 
}

