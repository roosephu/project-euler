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
template <typename T> T gcd(T x, T y) {for (T t; x; t = x, x = y % x, y = t); return y; }

template<class edge> struct Graph {
    vector<vector<edge> > adj;
    Graph(int n) {adj.clear(); adj.resize(n + 5);}
    Graph() {adj.clear(); }
    void resize(int n) {adj.resize(n + 5); }
    void add(int s, edge e){adj[s].push_back(e);}
    void del(int s, edge e) {adj[s].erase(find(iter(adj[s]), e)); }
    vector<edge>& operator [](int t) {return adj[t];}
};

const int64 N = 1e6;

// vector<pair<int, int>> G[900];

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    int64 ans = 0;

    int cnt = 0;
    FOR (i, 3, sqrt(N) * 2) {
        FOR (j, (i + 1) / 2, i) {
            if ((int64)i * j > 2 * N) break;
            if (gcd(i, j) == 1) {
                int x = i * i + j * j;
                if (x % 5 != 0) continue;
                x /= 5;
                int y = sqrt(x);
                if (y * y != x) continue;
                cerr << i << " " << j << " " << y << " " << (2ll * y - i) * (2ll * y + i) << " " << (j - y) * (j + y) << endl;
                ans += 2 * N / i / j;
                ++cnt;
                // ans ++;
            }
        }
    }

    
    // FOR (i, 1, 20) {
    //     FOR (j, i + 1, 20) {
    //         G[i * i + j * j].push_back(make_pair(i, j));
    //     }
    // }
    // FOR (i, 1, 800) {
    //     if (SZ(G[i]) == 2) {
    //         cerr << i << " ";
    //         for (auto x : G[i]) {
    //             cerr << "(" << x.car << ", " << x.cdr << ")";
    //         }
    //         cerr << endl;
    //     }
    // }

    cerr << ans << " " << cnt << endl;
    
    return 0; 
}
