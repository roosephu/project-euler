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

const int LMT = 1e8;

int prime[LMT + 2];

bool check(int x) {
    int lx = 1;
    for (int i = 1; i * i <= x; ++i) {
        if (i > lx * 2) return false;
        if (x % i == 0) lx = i;
    }
    if (x / lx > lx * 2) return false;
    // cout << "pass: " << x << endl;
    return true;
}

bool isP(int x) {
    for (int i = 1; prime[i] * prime[i] <= x; ++i)
        if (x % prime[i] == 0)
            return false;
    return true;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    
    for (int i = 2; i <= LMT; ++i) {
        if (!prime[i]) prime[++prime[0]] = i;
        for (int j = 1, k = LMT / i, t; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }

    // for (int i = 1; i <= prime[0]; ++i) {
    //     if (prime[i + 1] - prime[i    ] == 6 &&
    //         prime[i + 2] - prime[i + 1] == 6 &&
    //         prime[i + 3] - prime[i + 2] == 6) {
    //         int n = prime[i] + 9;
    //         if (n % 20 != 0) continue;
    //         cout << n << endl;
    //         if (check(n - 8) && check(n - 4) && check(n) && check(n + 4) && check(n + 8)) {
    //             cout << "Found: " << n << endl;
    //         }
    //     }
    // }
    for (int i = 1; i <= 100000000; ++i) {
        int n = 20 * i;
        if (isP(n - 3) && isP(n + 3) && check(n) && isP(n - 9) && isP(n + 9) && check(n - 4) && check(n + 4) && check(n + 8) && check(n - 8)) {
            cout << n << endl;
        }
    }

    return 0; 
}
