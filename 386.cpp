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

const int n = 1e8, N = n + 10;

int prime[N], lnk[N];

int f[100];

int calc(vector<int> &e) {
    memset(f, 0, sizeof(f));
    f[0] = 1;
    
    int s = 0;
    for (auto x : e)
        s += x;
    s /= 2;
    for (auto x : e)
        for (int t = s; t; --t)
            for (int i = 1; i <= x && i <= t; ++i)
                f[t] += f[t - i];
    return f[s];
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    // cout << calc({1, 1, 1}) << endl;
    
    for (int i = 2; i <= n; ++i) {
        if (!prime[i]) prime[++prime[0]] = i, lnk[i] = 1;
        for (int j = 1, k = n / i, t; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = 1, lnk[t] = i;
            if (i % prime[j] == 0) break;
        }
    }

    int64 ans = 1;
    for (int i = 2; i <= n; ++i) {
        vector<int> e;
        for (int j = i, lx = 0, c = 0; j; j = lnk[j]) {
            int d = lnk[j] ? j / lnk[j] : 0;
            if (d != lx) {
                if (c) e.push_back(c);
                lx = d, c = 1;
            } else {
                ++c;
            }
        }
        if (i == 128) {
            for (auto x : e)
                cout << "e: " << x << endl;
            cout << calc(e) << endl;
        }

        ans += calc(e);
        if (i % 1000000 == 1) cout << i << endl;
    }
    cout << ans << endl;

    return 0; 
}
