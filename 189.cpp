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

#include <gmpxx.h>

const int D = 8;

int64 F[10][60000];
int n;

void dfs(int d, int U, int ux, int B, int bx, int T) {
    if (d == n * 2 - 1) {
        assert(B < 60000);
        F[n][B] += F[n - 1][U] << T;
        return ;
    }
    if (d & 1) {
        dfs(d + 1, U * 3 + 0, 0, B, bx, T);
        dfs(d + 1, U * 3 + 1, 1, B, bx, T);
        dfs(d + 1, U * 3 + 2, 2, B, bx, T);
    } else {
        if (bx == ux || bx == 0 || ux == 0) dfs(d + 1, U, ux, B * 3 + 0, 0, T + (bx == 0 && ux == 0));
        if (bx == ux || bx == 1 || ux == 1) dfs(d + 1, U, ux, B * 3 + 1, 1, T + (bx == 1 && ux == 1));
        if (bx == ux || bx == 2 || ux == 2) dfs(d + 1, U, ux, B * 3 + 2, 2, T + (bx == 2 && ux == 2));
    }
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    F[0][0] = 1;
    for (n = 1; n <= D; ++n) {
        cout << n << endl;
        dfs(0, 0, -1, 0, -1, 0);
    }

    int64 ans = 0;
    for (int i = 0; i < 60000; ++i)
        ans += F[D][i];
    cout << "ans: " << ans << endl;

    return 0; 
}
