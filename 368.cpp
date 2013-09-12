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

const int P = 20, N = P * 100 + 1;

typedef real mat[N][N];

int cb[20][20];
mat G, U, t, w;

void matmul(mat a, mat b, mat c, int L) {
    memset(t, 0, sizeof(t));
    FOR (i, 0, N - 1) {
        FOR (j, 0, N - 1) {
            w[i][j] = b[j][i];
        }
    }
    FOR (i, 0, L - 1) {
        real *p = a[i];
        FOR (k, 0, N - 1) {
            real *q = w[k];
            FOR (j, 0, N - 1) {
                t[i][k] += p[j] * q[j];
            }
        }
    }
    memcpy(c, t, sizeof(t));
}

bool chk(int x) {
    if (x < 100) return true;
    return x % 1000 % 111 != 0 && chk(x / 10);
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cerr << setprecision(20) << endl;

    FOR (i, 0, 10) {
        FOR (j, 0, i) {
            cb[i][j] = j ? cb[i - 1][j - 1] + cb[i - 1][j] : 1;
        }
    }
    FOR (i, 0, 9) {
        FOR (j, 0, 9) {
            FOR (k, 0, 9) {
                if (i == j && j == k) continue;
                FOR (u, 1, P) {
                    FOR (v, u, P) {
                        G[(v - 1) * 100 + i * 10 + j][(u - 1) * 100 + j * 10 + k] += 1.0 * cb[v - 1][u - 1] * pow(-k, v - u) / pow(10, v);
                    }
                }
            }
        }
    }
    FOR (i, 0, 100 - 1) G[i][N - 1] = 1;
    G[N - 1][N - 1] = 1;
    
    FOR (i, 1, 9) {
        FOR (j, 0, 9) {
            FOR (t, 1, P) {
                U[0][(t - 1) * 100 + i * 10 + j] += 1 / pow(i * 10 + j, t);
            }
        }
    }
    FOR (i, 1, 9) U[0][N - 1] += 1.0 / i;

    const int T = 1000;
    // FOR (i, 0, N - 1) if (G[i][0]) {
    //     cerr << i << " " << G[i][0] << " " << U[0][i] << endl;
    // }
    FOR (i, 1, T - 1) {
        matmul(U, G, U, 1);
        cerr << i << " " << U[0][N - 1] << endl;
        matmul(G, G, G, N);
        // cerr << U[0][0] << endl;
    }
    // FOR (i, 1, 10) {
    //     matmul(U, G, U, 1)
    // }

    // cerr << G[100][1] << " " << G[0][1] << endl;
    // FOR (i, 0, 99) {
    //     ans += U[0][i];
    //     if (U[0][i]) cerr << i << " " << U[0][i] - 1.0 / i << endl;
    // }

    // double ok = 0;
    // FOR (i, 1, fpm(10, T, oo) - 1) if (chk(i)) ok += 1.0 / i; // else cerr << i << endl;
    cerr << U[0][N - 1] << endl;
    // cerr << chk(101100) << endl;

    return 0; 
}


