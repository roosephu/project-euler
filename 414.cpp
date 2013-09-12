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

const int64 MOD = 1e18;
const int B = 2000;

int b;
int v[5];
int64 w[B][B], f[B][B];

int64 sub(int64 x) {
    int64 p = 0, q = 0;
    FOR (i, 0, 4) v[i] = x % b, x /= b;
    sort(v, v + 5);
    FOR (i, 0, 4) p = p * b + v[i];
    ROF (i, 4, 0) q = q * b + v[i];
    return q - p;
}

int64 ways(int p, int q) {
    int64 t = 0;
    if (q == 0) {
        if (p == 0) {           // aaaaa
            t = 1; 
        } else {
            t += 120 / 24 * 2;   // aeeee aaaae
            t += 120 / 6 * (p - 1); // accce
        }
    } else if (p == q) {
        t += 120 / 2 / 2 * (p - 1); // aacee
        t += 120 / 6 / 2 * 2;       // aaaee aaeee
    } else {
        t += 120 / 2 * (q - 1); // abcee
        t += 120 / 2 / 2;       // abbee
        t += 120 / 6;           // abeee
        t *= 2;

        if (p - 2 >= q) {       // ab?de
            t += 120 / 2 * (p - 1 - q) * 2; // abbde, abdde
            t += 120 * (p - 1 - q) * (q - 1); // abcde
        }
    }
    return (b - p) * t;
}

// void dfs(int i) {
//     if (f[i] != -1) return ;
//     int j = sub(i);
//     if (j == 0 || j == i) f[i] = 0;
//     else {
//         dfs(j), f[i] = f[j] + 1;
//         if (f[j] == 0) {
//             FOR (x, 0, 4) cerr << i % b << " ", i /= b;
//             cerr << endl;
//         }
//     }
// }

// int64 calc() {
//     int t = fpm(b, 5, oo);
//     fill(f, f + t, -1);
    
//     int64 ans = 0;
//     FOR (i, 0, t) {
//         dfs(i);
//         ans += f[i];
//     }
//     return ans;
// }

pair<int, int> nxt(int x, int y) {
    int64 k = x * (fpm(b, 4, MOD) - 1ll) + y * (b * b - 1ll) * b;
    FOR (i, 0, 4) v[i] = k % b, k /= b;
    sort(v, v + 5);
    return make_pair(v[4] - v[0], v[3] - v[1]);
}

int dfs(int a, int b) {
    if (f[a][b] != -1) return f[a][b];
    auto x = nxt(a, b);
    if (x.car == a && x.cdr == b) return f[a][b] = 0;
    return f[a][b] = dfs(x.car, x.cdr) + 1;
}

int64 calc() {
    int64 t = fpm(b, 5, MOD);
    // fill(f, f + t, -1);

    FOR (i, 0, b - 1) {
        FOR (j, 0, i) {
            f[i][j] = -1; w[i][j] = 0;
        }
    }
    // memset(f, -1, sizeof(f));
    // memset(w, 0, sizeof(w));
    int64 ans = 0;
    // FOR (y, 0, t - 1) {
    //     int x = y;
    //     FOR (i, 0, 4) v[i] = x % b, x /= b;
    //     sort(v, v + 5);
    //     ++w[v[4] - v[0]][v[3] - v[1]];
    //     auto p = nxt(v[4] - v[0], v[3] - v[1]);
    //     auto q = sub(y);

    //     FOR (i, 0, 4) v[i] = q % b, q /= b;
    //     sort(v, v + 5);
    //     assert(p.car == v[4] - v[0] && p.cdr == v[3] - v[1]);
    // }
    int64 cnt = 0;
    FOR (i, 1, b - 1) {
        FOR (j, 0, i) {
            w[i][j] = ways(i, j);
            f[i][j] = dfs(i, j);

            cnt += w[i][j];
            assert(1.0 * w[i][j] * f[i][j] <= 1e18);
            (ans += w[i][j] * f[i][j]) %= MOD;
            // if (w[i][j] != ways(i, j)) {
            //     cerr << i << " " << j << " " << w[i][j] << " " << ways(i, j) << endl;
            // }
        }
    }
    // cerr << cnt << endl;
    return ans + t - b - 1;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    int64 ans = 0;
    FOR (t, 2, 300) {
        b = 6 * t + 3;
        (ans += calc()) %= MOD;
        cerr << t << endl;
        // cerr << b << " " << calc() << endl;
    }
    cerr << ans << endl;


    return 0; 
}

