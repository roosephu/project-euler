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

int64 ans = 0;
int T, N;

bool isP(int64 x) {
    for (int64 i = 2; i * i <= x; ++i)
        if (x % i == 0)
            return false;
    return true;
}

void dfs(int d, int m, int64 x) {
    if (d < m) return ;
    if (d == 0) {
        if (isP(x)) {
            ++N;
            ans += x;
            cout << x << endl;
        }
        return ;
    }
    
    for (int i = 0; i < 10; ++i) {
        if (d != 10 || i != 0) {
            dfs(d - 1, m - (i == T), x * 10 + i);
        }
    }
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    ans = 0;
    for (T = 0; T <= 9; ++T) {
        for (int M = 9; ; --M) {
            N = 0;
            dfs(10, M, 0);
            if (N != 0) break;
        }
    }
    cout << ans << endl;

    return 0; 
}
