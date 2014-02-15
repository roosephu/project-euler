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

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    int ans = 0;
    FOR (a, 0, 9) {
        FOR (b, 0, 9) {
            FOR (c, 0, 9) {
                FOR (g, 0, 9) {
                    FOR (j, 0, 9) {
                        int m = a + b + c - g - j;
                        if (m < 0 || m > 9) continue;
                        FOR (e, 0, 9) {
                            FOR (i, 0, 9) {
                                int S = a + e + i + m;
                                int d = S - a - b - c;
                                if (d < 0 || d > 9) continue;
                                FOR (f, 0, 9) {
                                    int h = S - e - f - g;
                                    if (h < 0 || h > 9) continue;
                                    int n = S - b - f - j;
                                    if (n < 0 || n > 9) continue;
                                    FOR (k, 0, 9) {
                                        int o = S - c - g - k;
                                        if (o < 0 || o > 9) continue;
                                        int l = S - i - j - k;
                                        if (l < 0 || l > 9) continue;
                                        int p = S - a - f - k;
                                        if (p < 0 || p > 9) continue;
                                        if (m + n + o + p != S || d + h + l + p != S) continue;
                                        ans++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << ans << endl;

    return 0; 
}
