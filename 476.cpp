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

const real pi = acos(-1);

real calc(real a, real b, real c) {
    real p = (a + b + c) / 2;
    real R = sqrt(p * (p - a) * (p - b) * (p - c)) / p;
    cout << R << endl;

    real m1 = 0, m2 = 0;
    for (int _ = 0; _ < 3; ++_) {
        real t = p - c;
        real r = (hypot(R, t) - R) / (1 + hypot(R, t) / R);
        cout << "r: " << r << endl;
        if (r > m1) m2 = m1, m1 = r;
        else if (r > m2) m2 = r;
        real x = a; a = b, b = c, c = x;
    }
    return pi * (R * R + m1 * m1 + m2 * m2);
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    cout << setprecision(15);

    real ans = 0; int cnt = 0;
    for (int a = 1; a <= 5; ++a)
        for (int b = a; a + b <= 5; ++b)
            for (int c = b; c < a + b; ++c) {
                ans += calc(a, b, c);
                cnt += 1;
            }
    cout << ans / cnt << endl;
    
    return 0; 
}
