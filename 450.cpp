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

const int N = 3.6e3;

struct node {
    int64 a, b, c;

    node(int A, int B, int C) : a(A), b(B), c(C) {}
} ;

bool operator < (const node &a, const node &b) {
    return a.a == b.a ? (a.b < b.b) : (a.a < b.a);
}

node operator * (const node &a, const node &b) {
    return node(a.a * b.a - a.b * b.b, a.a * b.b + a.b * b.a, a.c * b.c);
}

int cnt;
set<node> S;

void test(int a, int b, int c) {
    auto p = node(a, b, c);
    if (S.count(p)) return ;
    vector<node> v;
    for (auto q = p; q.c < N; q = q * p) v.push_back(q), S.insert(q);

    for (int i = 0; i < SZ(v); ++i) {
        for (int j = i + 1; j < SZ(v); ++j) {
            int x = gcd(i + 1, j + 1);
            int pr = N * (i + 1) / (i + j + 2) / v[j].c;
            for (int t = 1; t <= pr; ++t) {
                int64 r = t * v[j].c * (i + 1) / x, R = t * v[j].c * (j + 1) / x;
                if (r == 500 && R == 1500)
                    cout << r << " " << R << " " << (R * v[i].a / v[i].c + r * v[j].a / v[j].c) << " " << (R * v[i].b / v[i].c - r * v[j].b / v[j].c) << endl;
            }
        }
    }
}

void gen(int a, int b, int c) {
    if (c > N) return ;
    if (a && b) test(a, b, c);
    ++cnt;
    int g = (a + b + c) << 1, d, e, f;
    gen(d = g - a, e = g - b, f = g + c);
    if (a) g = (a <<= 1) << 1, gen(d - a, e - g, f - g);
    if (b) g = (b <<= 1) << 1, gen(d - g, e - b, f - g);
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    gen(3, 4, 5);
    gen(4, 3, 5);
    cout << cnt << endl;

    return 0; 
}
