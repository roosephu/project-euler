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

bool e;

typedef pair<real, real> point;

point f(real a, real b, point x, real t) {
    t = tan(t);
    real k = x.snd - x.fst * t;
    real A = 1 / a / a + t * t / b / b, B = 2 * t * k / b / b, C = k * k / b / b - 1;
    real D = B * B - 4 * A * C;
    if (D < 0) e = true;
    real x0 = (-B + sqrt(D)) / (2 * A), x1 = (-B - sqrt(D)) / (2 * A);
    real z = abs(x0 - x.fst) <= 1e-6 ? x1 : x0;
    return make_pair(z, t * (z - x.fst) + x.snd);
}

real dist(point a, point b, point x) {
    real A = a.snd - b.snd, B = b.fst - a.fst, C = a.fst * b.snd - a.snd * b.fst;
    return abs(A * x.fst + B * x.snd + C) / hypot(A, B);
}

bool check(real a, real b, real t) {
    point x = make_pair(a / 2, sqrt(3) * b / 2), y = make_pair(2 * b, 0);
    real c = atan2(sqrt(3) * b / 2, a / 2 - b * 2);
    e = false;
    point L = f(a, b, x, c - t);
    point R = f(a, b, x, c + t);
    if (e) return false;
    cout << dist(x, L, y) << " " << dist(x, R, y) << " " << dist(L, R, y) << endl;
    return dist(x, L, y) < dist(L, R, y);
}

const real pi = acos(-1);

const int N = 1e7;

real H[N + 1];

real calc(int n) {
    real ans = 0;
    // for (int a = 3; a <= n; ++a)
    //     for (int b = 1; b <= (a - 1) / 2; ++b)
    //         ans += (a - b * 2.0) / (a - b) * b;
    for (int y = 1; y <= (n - 1) / 2; ++y) {
        ans += y * (n - 2.0 * y) - 1.0 * y * y * (H[n - y] - H[y]);
    }
    return ans;
}

real C(real n, int x) {
    real ret = 1;
    for (int i = 1; i <= x; ++i) {
        ret *= n;
        ret /= i;
        n -= 1;
    }
    return ret;
}

real h(real n) {
    return log(n) + 0.5772156649 + 1 / (2 * n) - 1 / (12 * n * n);
}

real S(real n, int o) {
    return C(n, o + 1) * (h(n) - 1.0 / (o + 1)); // H[(int)(n + 1e-3)]
}


real f1(real n, real y) {
    return (n - 2) * C(y, 2) - 4 * C(y, 3) + 2 * S(y, 2) + S(y, 1);
}

real f2(real n, real y) {
    return n * n * S(y, 0) + 2 * S(y, 2) - (2 * n - 1) * S(y, 1);
}

real F(int64 n) {
    int64 L = (n - 1) / 2;
t    // real t = 0;
    // for (int y = n - L; y <= n - 1; ++y)
    //     t += 1.0 * (n - y) * (n - y) * H[y];
    // cout << "---" << (f2(n, n) - f2(n, n - L)) << " " << t << endl;
    // t = 0;
    // for (int y = 1; y <= L; ++y) {
    //     t += y * (n - 2.0 * y) + y * y * H[y];
    // }
    // cout << "---" << (f1(n, L + 1) - f1(n, 1)) << " " << t << endl;
    
    return (f1(n, L + 1) - f1(n, 1)) - (f2(n, n) - f2(n, n - L));
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    cout << setprecision(15);
    for (int i = 1; i <= N; ++i)
        H[i] = H[i - 1] + 1.0 / i;
    
    // real a = 5, b = 1;
    // real L = 0, R = pi / 2, m;
    // for (; m = (R + L) / 2, R - L > 1e-7; )
    //     check(a, b, m) ? (L = m) : (R = m);

    int n = 10;
    // for (int i = 1; i <= 10; ++i)
    //     for (int j = 0; j <= 2; ++j)
    //         cout << i << " " << j << " " << S(i, j) << endl;
    // for (int i = 3; i <= 100; ++i)
    //     cout << calc(i) << " " << F(i) << endl;
    cout << F(1e11) << endl;
    
    return 0; 
}
