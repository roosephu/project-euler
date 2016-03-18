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

/*
  simple digital DP.

  let f(i, j, k, l) be the # of k's in {s(0), ..., s(2^i - 1)}, given the prefix has sum j and last bit l.
  f(i, j, k, l) = f(i - 1, j + ??, k, 0) + f(i - 1, j + ???, k - start, 1)
 */

int64 count(int64 n, int x) {
    int64 ret = 0, start = 0; int now = 0;
    for (int hi = 62; hi >= 0; --hi)
        if (n >> hi & 1) {
            if (now & 1) {
                start = -start;
                x = -x;
            }
            int64 mid = start, dff = 1ull << ((hi + 1) >> 1);
            if (hi & 1) {
                int64 d = x - start;
                if (d < dff)
                    ret += max(d, 0ll);
                else if (d == dff)
                    ret += dff / 2;
                start += dff;
            } else {
                mid += dff;
                ret += max(0ll, dff - abs(mid - x));
                start = mid;
            }
            if (now & 1) {
                start = -start;
                x = -x;
            }
            now += (n >> hi) % 4 == 3;
        }
    return ret;
}

int64 pos(int64 x, int64 y) {
    int64 m;
    for (int64 L = 1, R = (1ll << 62) - 1; m = (L + R) >> 1, L < R; )
        count(m, x) >= y ? (R = m) : (L = m + 1);
    return m;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    int a = 1, b = 2;

    int64 ans = 0;
    for (int i = 2; i <= 45; ++i) {
        int64 t = pos(b, a);
        cout << t << " " << count(t, b) << " " << a << endl;
        ans += t - 1;
        
        int64 c = b + a;
        a = b, b = c;
    }
    cout << ans << endl;
    // count(312, 25);
    cout << count(1220847710ll + 1, 54321) << " " << pos(54321, 12345) - 1 << endl;
    // for (int i = 1; i <= 60; ++i)
    //     cout << count(312, i) << " ";

    return 0; 
}
