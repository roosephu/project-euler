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

const int LMT = 1e5;

int prime[LMT + 1];
int cnt = 0;
int64 ans = 0;
set<int> S;

bool check(int n) {
    for (int i = 1; prime[i] * prime[i] <= n; ++i)
        if (n % prime[i] == 0)
            return false;
    return true;
}

void nxt(int n) {
    cout << n << " ";
    int m = 2;
    for (++n; !check(++n); )
        ++m;
    cout << m << endl;
    S.insert(m);
    // ans += n;
}

void dfs(int64 x, int y) {
    x *= prime[y];
    if (x > 1e9) return ;
    ++cnt, nxt(x);
    // cout << x << endl;
    dfs(x, y    );
    dfs(x, y + 1);
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    for (int i = 2; i <= LMT; ++i) {
        if (!prime[i]) prime[++prime[0]] = i;
        for (int j = 1, k = LMT / i, t; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }

    dfs(1, 1);
    for (auto x : S)
        ans += x;
    cout << cnt << " " << ans << endl;

    return 0; 
}
