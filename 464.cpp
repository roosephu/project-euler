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

const int n = 2e7, N = n + 10;

int prime[N], mu[N];
pair<int64, int64> f[N];
int64 w[N];
map<int64, int> bit;

void modify(int64 x) {
    for (; ~x >> 32 & 1; x += x & -x)
        ++bit[x];
}

int query(int64 x) {
    int t = 0;
    for (; x; x &= x - 1)
        t += bit[x];
    return t;
}

bool cmp(const pair<int64, int64> &a, const pair<int64, int64> &b) {
    auto k = (a.snd * 100 - a.fst * 99) - (b.snd * 100 - b.fst * 99);
    if (k != 0) return k < 0;
    return a.fst < b.fst;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    for (int i = 2; i <= n; ++i) {
        if (!prime[i]) prime[++prime[0]] = i, mu[i] = -1;
        for (int t, j = 1, k = n / i; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = 1;
            if (i % prime[j]) mu[t] = -mu[i];
            else {mu[t] = 0; break; }
        }
    }
    mu[1] = 1;
    for (int i = 1; i <= n; ++i) {
        f[i] = f[i - 1];
        if (mu[i] > 0) ++f[i].fst;
        if (mu[i] < 0) ++f[i].snd;
    }
    sort(f, f + n + 1, cmp);

    int64 ans = 0;
    for (int i = 0; i <= n; ++i) {
        // ans += query();
        // modify();
        auto &x = f[i];
        w[i] = x.fst * 100 + (n - x.snd) * 99;
        // for (int j = 0; j < i; ++j) {
        //     if (w[j] <= w[i]) {
        //         // int64 P = f[i].fst - f[j].fst, N = f[i].snd - f[j].snd;
        //         // cout << P << " " << N << " " << w[i] << " " << w[j] << endl;
        //         // cout << P << " " << N << " " << 100 * P - 99 * N << " " << 100 * N - 99 * P << endl;
        //         ++ans;
        //     }
        // }
        ans += query(w[i]);
        modify(w[i]);
        if (i % 10000 == 0) cout << i << endl;
        // cout << x.fst << " " << x.snd << " " << 100 * x.snd - 99 * x.fst << endl;
    }
    cout << ans << endl;

    return 0; 
}
