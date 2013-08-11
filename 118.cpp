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
#define For(i, a, b) for (int _end_ = (b), i = (a); i <= _end_; ++i)
#define Rof(i, a, b) for (int _end_ = (b), i = (a); i >= _end_; --i)
#define FOR(i, a, b) for (int _end_ = (b), i = (a); i != _end_; ++i)
#define ROF(i, a, b) for (int _end_ = (b), i = (a); i != _end_; --i)

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

const int N = 1e8;

int primes[N + 1];
int64 f[1 << 9];

void get_primes(int n) {
    FOR (i, 2, n + 1) {
        if (!primes[i]) primes[++primes[0]] = i;
        for (int j = 1, k = n / i; primes[j] <= k; ++j) {
            primes[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    get_primes(N);

    f[0] = 1;
    FOR (i, 1, primes[0] + 1) {
        int m = 0, b = true;
        for (int x = primes[i]; x; x /= 10) {
            int y = x % 10;
            if (y == 0 || (m >> (y - 1) & 1)) b = false;
            if (y) m |= 1 << (y - 1);
        }
        if (!b) continue;

        cerr << primes[i] << endl;
        ROF (S, (1 << 9) - 1, -1) {
            if (S & m) continue;
            f[S | m] += f[S];
        }
    }
    cout << f[(1 << 9) - 1] << endl;

    return 0; 
}
