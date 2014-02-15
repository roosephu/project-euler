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
    Graph(int n = 0) {adj.clear(); adj.resize(n + 5);}
    void resize(int n) {adj.resize(n + 5); }
    void add(int s, edge e){adj[s].push_back(e);}
    void del(int s, edge e) {adj[s].erase(find(iter(adj[s]), e)); }
    vector<edge>& operator [](int t) {return adj[t];}
};

const int N = 100, n = 80;

Graph<pair<int, int>> G(N * N);
int dist[N * N], link[N * N], x[N][N];

int getint() {
    int t; char c;
    for (; !isdigit(c = getchar()); );
    for (t = c - '0'; isdigit(c = getchar()); )
        t = t * 10 + c - '0';
    return t;
}

int main(int argc, char **argv) {
    freopen("82.txt", "r", stdin);
    
    ios_base::sync_with_stdio(false);

    int S = n * n + 1, T = S + 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            x[i][j] = getint();
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int v = (i - 1) * n + j;
            if (j == 1) G.add(S, make_pair(v, x[i][j]));
            else G.add(v, make_pair(v - 1, x[i][j - 1]));
            if (j == n) G.add(v, make_pair(T, 0));
            else G.add(v, make_pair(v + 1, x[i][j + 1]));

            if (i != 1) G.add(v, make_pair(v - n, x[i - 1][j]));
            if (i != n) G.add(v, make_pair(v + n, x[i + 1][j]));
        }
    }

    memset(dist, 0x3f, sizeof(dist)), dist[S] = 0;
    int head = S, tail = S, v, dtmp;
    for (; head; head = link[v], link[v] = 0)
        for (auto e : G[v = head])
            if ((dtmp = dist[v] + e.snd) < dist[e.fst]) {
                dist[e.fst] = dtmp;
                if (link[e.fst] || e.fst == tail) continue;
                if (head != tail && dist[link[v]] > dtmp)
                    link[e.fst] = link[v], link[v] = e.fst;
                else
                    link[tail] = e.fst, tail = e.fst;
            }
    cout << dist[T] << endl;

    return 0; 
}
