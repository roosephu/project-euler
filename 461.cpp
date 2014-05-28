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

const int n = 1e4, N = 1.1e8, M = 1e5;
const real pi = acos(-1);

real D[N];
real v[M];

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    int K = 0, m = 0;
    for (int i = 0; ; ++i) {
        v[i] = exp(1.0 * i / n) - 1;
        if (v[i] <= pi) m = i;
        else break;
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = i; j <= m; ++j) {
            D[++K] = v[i] + v[j];
        }
    }
    sort(D + 1, D + K + 1);

    real ans = 1e300; int xi, xj;
    for (int i = 1, j = K; i <= K; ++i) {
        for (; j && D[i] + D[j] > pi; --j);
        if (j > 0 && pi - (D[i] + D[j]) < ans) {
            ans = pi - (D[i] + D[j]);
            xi = i, xj = j;
        }
        if (j < K && (D[i] + D[j + 1]) - pi < ans) {
            ans = (D[i] + D[j + 1]) - pi;
            xi = i, xj = j + 1;
        }
    }
    cout << setprecision(20) << ans << " " << xi << " " << xj << endl;

    for (int i = 1; i <= m; ++i) {
        for (int j = i; j <= m; ++j) {
            if (v[i] + v[j] == D[xi])
                cout << "xi: " << i << " " << j << endl;
            if (v[i] + v[j] == D[xj])
                cout << "xj: " << i << " " << j << endl;
        }
    }

    return 0; 
}
