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
#ifdef DEBUG
#define cvar(x) cerr << "<" << #x << ": " << x << ">"
#define evar(x) cvar (x) << endl
template<class T> void DISP(const char *s, T x, int n) {cerr << "[" << s << ": "; for (int i = 0; i < n; ++i) cerr << x[i] << " "; cerr << "]" << endl;}
#define disp(x,n) DISP(#x " to " #n, x, n)
#else
#define cvar(...) ({})
#define evar(...) ({})
#define disp(...) ({})
#endif
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
     Graph(int n) {adj.clear (); adj.resize (n + 5);}
     Graph() {adj.clear (); }
     void resize(int n) {adj.resize (n + 5); }
     void add(int s, edge e){adj[s].push_back (e);}
     void del(int s, edge e) {adj[s].erase (find (iter (adj[s]), e)); }
     vector<edge>& operator [](int t) {return adj[t];}
};

const int N = 10000000 - 1, LMT = N / 4;

int dvs[LMT + 1];

int exgcd(int a, int b, int &p, int &q) {
    if (b == 0) return p = 1, q = 0, a;
    int k = a / b, t = exgcd(b, a % b, q, p);
    return q -= k * p, t;
}

int main(int argc, char **argv) {
     ios_base::sync_with_stdio(false);

     FOR (i, 1, LMT) {
         FOR (j, 1, LMT / i) {
             ++dvs[i * j];
         }
     }

     cerr << 1000.0 * clock() / CLOCKS_PER_SEC << endl;
     int cnt1 = 0, cnt2 = 0; int64 rmax = 0;
     int64 ans = 0;
     FOR (u, 1, 2 * sqrt(N) + 1) {
         FOR (v, 1, u - 1) {
             if ((u ^ v) & 1) continue;
             int s = (u * u + v * v) / 2, k = (u + v) * (u - v) / 4;
             if (s > N) break;
             int p, q, g = exgcd(u, v, p, q);
             if (s % g != 0) continue;
             // cerr << u << " " << v << " " << p << " " << q << " " << s << " " << g << endl;
             int lcm = u * v / g, y = v / g;
             int64 ls = (int64)lcm * lcm;
             p = ((int64)p * (s / g) % y + y) % y;
             q = (s - p * u) / v;
             // cerr << u << " " << v << " " << p << " " << q << " " << s << endl;
             // assert(p * u + q * v == s && 0 <= p && p < v / g);

             int A = p * u - k, D = s - A;
             if (A <= k) {
                 int d = (k - A) / lcm + 1;
                 A += d * lcm;
                 D -= d * lcm;
             }
             for (; D > k; A += lcm, D -= lcm) {
                 ++cnt1;
                 int64 r = (int64)A * D - (int64)k * k;
                 if (r % ls != 0) continue;
                 ++cnt2;
                 r /= ls;
                 // cerr << r << endl;
                 chkmax(rmax, r);
                 ans += dvs[r];
                 // FOR (i, 1, r) {
                 //     if (r % i != 0) continue;
                 //     cerr << A << " " << i * lcm << " " << r / i * lcm << " " << D << endl;
                 // }
                 // assert((A + k) % u == 0 && (A - k) % v == 0);
             }
             // FOR (A, 1, s - 1) {
             //     if ((s + k) % u == 0 && (s - k) % v == 0) {
             //         ++ans;
             //     }
             // }
         }
     }
     cerr << 1000.0 * clock() / CLOCKS_PER_SEC << endl;
     cout << ans << " " << cnt1 << " " << cnt2 << " " << rmax << endl;
     return 0; 
}

