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

const int n = 1e8, N = n + 10;

int prime[N / 10], Q[100], cnt[10000];
bool o[N];
Graph<int> G(10000);

void init() {
    int i, j, k, t;
    for (i = 2; i <= n; ++i) {
        if (!o[i]) prime[++prime[0]] = i;
        for (j = 1, k = n / i; prime[j] <= k; ++j) {
            o[t = i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

bool chk(int a, int b) {
    int a1 = a, b1 = b;
    for (int k = b; k; k /= 10, a1 *= 10);
    for (int k = a; k; k /= 10, b1 *= 10);
    return !o[a1 + b] && !o[b1 + a];
}

void dfs(int v, int c) {
    if (v == 0) return ;
    if (c == 5) {
        int s = 0;
        for (int i = 0; i < c; ++i) cout << Q[i] << " ", s += Q[i];
        cout << s << endl;
        return ;
    }
    if (c) dfs(v - 1, c);
    if (cnt[v] != c) return;
    Q[c] = prime[v];
    for (auto c : G[v])
        ++cnt[c];
    dfs(v - 1, c + 1);
    for (auto c : G[v])
        --cnt[c];
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    init();
    for (int i = 1; i <= prime[0]; ++i) {
        for (int j = 1; j < i; ++j) {
            if (chk(prime[i], prime[j])) {
                G[i].push_back(j);
            }
        }
        dfs(i, 0);
    }

    return 0; 
}
