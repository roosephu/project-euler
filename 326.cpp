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

#include <gmpxx.h>
#include <gmp.h>

typedef mpz_class ZZ;

const ZZ N = 1e12;
const int M = 1e6, L = 1e8;

int a[L], f[L];
ZZ cnt[M];

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    a[1] = 1; f[0] = -1;

    int j = 0, P = 0;
    ZZ s = 1;
    FOR (i, 2, L) {
        ZZ x = s % i;
        a[i] = x.get_si();
        s += (ZZ)a[i] * i;
        (a[i] += a[i - 1]) %= M;
        for (; j >= 0 && a[j + 1] != a[i]; j = f[j]);
        f[i] = ++j;
        if (f[i] * 2 == i) {
            P = f[i];
            break;
        }
    }
    cerr << P << " " << s << endl;
    FOR (i, 1, P) {
        assert(a[i] == a[i + P]);
        // cerr << a[i] << " " << a[i + P] << endl;
    }
    ZZ ans = 0;
    FOR (i, 1, P) {
        cnt[a[i]] += ((ZZ)N + P - i) / P;
    }
    cnt[0] += 1;
    FOR (i, 0, M - 1) {
        ans += cnt[i] * (cnt[i] - 1) / 2;
    }
    cerr << ans << endl;
    
    return 0; 
}
