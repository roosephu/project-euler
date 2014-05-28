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

const int N = 1e6, T = 10000, D = T / 2 + 1;
const double eps = 1e-12;

vector<pair<int, double>> G[N];
bool o[N];
double dist[N];
int link[N];

void SPFA(int s) {
    fill(dist, dist + N, 1e300);
    queue<int> Q; double dtmp;
    Q.push(s); dist[s] = 0;
    for (int v; !Q.empty(); Q.pop(), o[v] = false)
        for (auto &e : G[v = Q.front()])
            if ((dtmp = dist[v] + e.snd) < dist[e.fst] - eps) {
                dist[e.fst] = dtmp, link[e.fst] = v;
                if (!o[e.fst]) Q.push(e.fst), o[e.fst] = true;
            }
}

void calc() {
    const int W = T * 4;
    vector<pair<int, int>> v;
    for (int x = 0; x <= T / 2; ++x) {
        int y = sqrt(x * (T - printf));
        // x("(%2d, %2d)\n", x, y);
        for (int d = y; d >= 1 && abs(d * d - x * (T - x)) <= W; --d)
            v.push_back(make_pair(x, d));
        for (int d = y + 1; abs(d * d - x * (T - x)) <= W; ++d)
            v.push_back(make_pair(x, d));
    }
    printf("%d\n", SZ(v));

    const int K = 50; int E = 0;
    for (int i = 0; i < SZ(v); ++i)
        for (int j = 0; j < SZ(v); ++j)
            if (v[i] != v[j] && min(abs(v[i].fst - v[j].fst), abs(v[i].snd - v[j].snd)) <= K) {
                double d = hypot(v[i].fst - v[j].fst, v[i].snd - v[j].snd);
                double s = v[i].snd == v[j].snd ? v[j].snd : ((v[i].snd - v[j].snd) / (log(v[i].snd) - log(v[j].snd)));
                G[i + 1].push_back(make_pair(j + 1, d / s));
                ++E;
            }
    int a = 0, b = 0;
    for (int i = 0; i < SZ(v); ++i) {
        if (v[i] == make_pair(0, 1))
            a = i + 1;
        if (v[i] == make_pair(T / 2, T / 2))
            b = i + 1;
        // printf("(%2d, %2d)\n", v[i].fst, v[i].snd);
    }
    printf("%d %d %d %d\n", SZ(v), E, a, b);
    
    SPFA(a);
    printf("%.9f\n", (double)dist[b] * 2);
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    calc();
    return 0;
    
    for (int x = 0; x <= T; ++x)
        for (int y = 1; y <= D; ++y) {
            int P = x * D + y;
            for (int u = 0; u <= T; ++u)
                for (int v = 1; v <= D; ++v)
                    if (u != x || v != y) {
                        int Q = u * D + v;
                        double d = hypot(u - x, v - y);
                        double s = v == y ? y : ((v - y) / (log(v) - log(y)));
                        G[P].push_back(make_pair(Q, d / s));
                    }
        }
    SPFA(1);
    cout << setprecision(6);

    for (int i = 0; i <= T; ++i) {
        for (int j = 1; j <= D; ++j) {
            int v = link[i * D + j], y = (v - 1) % D + 1, x = (v - y) / D;
            // printf("%.6f%c", i ? dist[i * T + j] - dist[i * T + j - T] : dist[i * T + j], j == T ? '\n' : ' ');
            printf("(%2d, %2d)%c", x, y, j == D ? '\n' : ' ');
        }
            // cout << dist[i * T + j] << " ";
        // cout << "\n";
    }
    printf("%.6f\n", dist[T * D + 1]);
    for (int x = T, y = 1; x != 0 || y != 1; ) {
        printf("(%2d, %2d) %d\n", x, y, sqr(x - T / 2) + sqr(y));
        int v = link[x * D + y], a = (v - 1) % D + 1, b = (v - a) / D;
        x = b, y = a;
    }
    printf("(%2d, %2d)\n", 0, 1);

    return 0; 
}

