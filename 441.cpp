#include <complex>
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

typedef complex<double> CC;

const int bT = 25, T = 1 << bT, N = 11000000, n = 10000000;
const long double pi = acos(-1);

CC *fwd, *inv, X[T], Y[T];
long double g[N], f[N], H[N], F[N], H2[N];
int prime[N], mu[N];

void FFT(CC *x, int bn, CC *w) {
    cerr << "FFT" << endl;
    int n = 1 << bn;
    for (int i = 0, j = 0; i < n; ++i) {
        if (i < j) swap(x[i], x[j]);
        for (int k = 1 << bn >> 1; (j ^= k) < k; k >>= 1);
    }
    FOR (i, 1, bn) {cerr << "FFT: " << i << endl;
        FOR (j, 0, (1 << (bn - i)) - 1) {
            FOR (k, 0, (1 << i >> 1) - 1) {
                int s = (j << i) | k, t = s | 1 << (i - 1);
                CC o = w[(T >> i) * k], u = x[s] + x[t] * o, v = x[s] - x[t] * o;
                x[s] = u;
                x[t] = v;
            }
        }
    }
}

void calc_g() { // compute g[k] = sum_{i + j = k} \frac{1}{ij}
    FOR (i, 1, n) X[i] = 1.0 / i;
    FFT(X, bT, fwd);
    FOR (i, 0, T - 1) X[i] *= X[i];
    FFT(X, bT, inv);
    FOR (i, 1, N) g[i] = X[i].real() / T;
}

void calc_f() {
    memset(X, 0, sizeof(X)), memset(Y, 0, sizeof(Y));
    FOR (i, 1, n) H[i] = H[i - 1] + 1.0 / i, H2[i] = H2[i - 1] + 1.0 / i / i;
    FOR (i, 1, n) X[i] = 1.0 / i, Y[i] = H[i];
    FFT(X, bT, fwd), FFT(Y, bT, fwd);
    FOR (i, 0, T - 1) X[i] *= Y[i];
    FFT(X, bT, inv);
    FOR (i, 1, N) f[i] = H[i] * H[i] - X[i].real() / T;
}

void get_mu() {
    mu[1] = 1;
    FOR (i, 2, N - 1) {
        if (!prime[i]) prime[++prime[0]] = i, mu[i] = -1;
        for (int j = 1, t, k = (N - 1) / i; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = 1;
            if (i % prime[j]) mu[t] = -mu[i];
            else {mu[t] = 0; break; }
        }
    }
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    fwd = new CC[T];
    inv = new CC[T];
    FOR (i, 0, T - 1) {
        double w = 2 * pi * i / T;
        fwd[i] = CC(cos(w), +sin(w));
        inv[i] = CC(cos(w), -sin(w));
    }
    calc_g();
    calc_f();

    FOR (i, 1, n / 2) g[i * 2] -= 1.0 / i / i;
    FOR (i, 1, n) g[i] /= 2, f[i] = (f[i] - H2[i] + H2[i / 2]) / 2;
    FOR (i, 1, n) g[i] += g[i - 1], F[i] = F[i - 1] + f[i];

    get_mu();
    double ans = 0;
    FOR (d, 1, n) {
        if (mu[d] == 0) continue;
        double coef = 1.0 * mu[d] / d / d, aux = 0;
        aux += g[n / d];
        aux += F[n / d - 1] * d + f[n / d] * (n % d + 1);

        // FOR (x, 1, n) {
        //     double t = aux;
        //     FOR (i, 1, x / d) {
        //         FOR (j, i + 1, x / d) {
        //             if ((i + j) * d >= x) {
        //                 aux += 1.0 / (i * j);
        //             }
        //         }
        //     }
        //     // cerr << aux - t << " " << f[x / d] / d / d << endl;
        // }
        // cerr << d << " " << aux << " " << (F[n / d - 1] * d + f[n / d] * (n % d + 1)) / d / d << endl;
        ans += coef * aux;
    }

    // FOR (x, 1, n) {
    //     FOR (i, 1, x) {
    //         FOR (j, i + 1, x) {
    //             if (gcd(i, j) == 1 && i + j >= x)
    //                 ans += 1.0 / i / j;
    //         }
    //     }
    // }
    cout << setprecision(20) << ans << endl;

    return 0; 
}

