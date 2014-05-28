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

const int n = 1000, N = n + 10;

int f[N], V[N], K[N];

string bin(int x) {
    string t = "";
    for (; x; x >>= 1)
        t = (char)(x % 2 + '0') + t;
    return t;
}

int F(int i, int j) {
    return 1 + (j <= 2 ? 0 : (1 + f[j - 2])) + (j >= i - 1 ? 0 : (1 + f[i - j - 1]));
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    f[-1] = f[0] = -1;
    for (int i = 1; i <= n; ++i) {
        if (i >= 3)
            f[i] = 1 + f[(i - 1) / 2] + f[i / 2];
        int k = 0, v = 0;
        for (int j = 1; j <= i; ++j) {
            int t = F(i, j);
            if (t > k) k = t, v = 1;
            else if (t == k) ++v;
            // cout << "-- " << i << " " << k << " " << t << endl;
        }
        // if (i == 13) {
        //     for (int j = 1; j <= i; ++j) {
        //         int t = F(i, j);
        //         if (t == k) {
        //             cout << "-- " << j - 2 << " " << i - j - 1 << endl;
        //         }
        //         // cout << "-- " << i << " " << k << " " << t << endl;
        //     }
        // }
        // if (i >= 2) {
        //     int x = 32 - __builtin_clz(i);
        //     cout << i << " " << f[i] << " " << max((1 << (x - 2)) - 1, i - (1 << (x - 1))) << endl;
        //     assert(f[i] == max((1 << (x - 2)) - 1, i - (1 << (x - 1))));
        // }
        // cout << i << " " << k << " " << v << " " << f[i] << endl;
        V[i] = v, K[i] = k;

        int t = F(i, 1);
        for (int j = 1; j < i; j <<= 1)
            if (F(i, j + 1) == k)
                cout << ">>> " << i - 1 << " " << j << endl;
        // cout << i << " " << k << " " << t << endl;
        // assert(k == t);

        // cout << V[i] << " " << V[i / 2] << endl;
        
        // if (K[i] == K[i - 1] && V[i] == V[i - 1] * 2 + 2)
        //     cout << i << " " << v << " " << k << endl;
        // cout << i << " " << f[i] << endl;
    }
    // for (int i = 1; i <= n; ++i) {
    //     int t = 0;
    //     for (int j = i; j <= n; ++j) {
    //         if (F(j, i) == K[i])
    //             ++t;
    //     }
    //     cout << i << " " << t << endl;
    // }

    return 0; 
}
