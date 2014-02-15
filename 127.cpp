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

const int n = 120000 - 1, N = n + 10;

int rad[N], lmt[N], Q[N];

int get_rad(int n) {
    int ret = 1;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            ret *= i;
            for (; n /= i, n % i == 0; );
        }
    }
    if (n != 1) ret *= n;
    return ret;
}

bool cmp(int a, int b) {return lmt[a] > lmt[b]; }

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    for (int i = 1; i <= n; ++i)
        rad[i] = get_rad(i), lmt[i] = i / rad[i];

    vector<int> Q;
    for (int i = 1; i <= n; ++i)
        if (lmt[i] != 1)
            Q.push_back(i);
    sort(ALL(Q), cmp);
    
    int64 ans = 0;
    for (int a = 1; a < n; ++a) {
        for (int c : Q) {
            if (lmt[c] < rad[a]) break;
            if (c > a * 2 && gcd(a, c) == 1 && rad[a] * rad[c - a] < lmt[c])
                ans += c; //, cout << a << " " << b << " " << a + b << endl;
        }
        // cout << a << " " << ans << endl;
    }
    cout << ans << endl;

    return 0; 
}
