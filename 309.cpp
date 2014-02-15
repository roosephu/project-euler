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

const int LMT = 1e6 - 1;

vector<pair<int, int>> G[LMT + 1];
set<pair<pair<int, int>, int>> M;

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    FOR (i, 0, 1e3) {
        FOR (j, 1, i - 1) {
            if (gcd(i, j) == 1) {
                int a = i * i - j * j;
                int b = 2 * i * j;
                int c = i * i + j * j;
                FOR (x, 1, LMT / c) {
                    G[a * x].push_back(make_pair(b * x, c * x));
                    G[b * x].push_back(make_pair(a * x, c * x));
                }
            }
        }
    }

    FOR (w, 1, LMT) {
        if (w % 1000 == 0) cerr << w << endl;
        sort(ALL(G[w]));
        for (auto &p : G[w]) {
            for (auto &q : G[w]) {
                if (p.car == q.car) break;
                if (((int64)p.car * q.car) % (p.car + q.car) == 0) {
                    M.insert(make_pair(make_pair(p.car, q.car), w));
                    // cerr << p.cdr << " " << q.cdr << " " << (p.car * q.car) / (p.car + q.car) << endl;
                }
            }
        }
    }
    cout << SZ(M) << endl;

    return 0; 
}
