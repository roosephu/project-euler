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

typedef pair<int, int> seg;

set<seg> S;

void merge(seg x) {
    auto q = S.lower_bound(x), p = q;
    if (q != S.end() && x.cdr + 1 == q->car) {
        x.cdr = q->cdr;
        S.erase(q);
    }
    if (p != S.begin()) {
        --p;
        if (p->cdr + 1 == x.car) {
            x.car = p->car;
            S.erase(p);
        }
    }
    S.insert(x);
}

void insert(int x) {
    auto q = S.lower_bound(make_pair(x, x)), p = q;
    if (q != S.begin()) {
        --p;
        auto s = *p;
        if (s.car <= x && x <= s.cdr) {
            S.erase(p);
            int c = s.car + s.cdr - x;
            merge(make_pair(s.car - 1, c - 1));
            merge(make_pair(c + 1, s.cdr + 1));
            return ;
        }
    }
    if (q != S.end()) {
        auto s = *q;
        if (s.car <= x && x <= s.cdr) {
            S.erase(q);
            int c = s.car + s.cdr - x;
            merge(make_pair(s.car - 1, c - 1));
            merge(make_pair(c + 1, s.cdr + 1));
            return ;
        }
    }
    merge(make_pair(x, x));
}

const int V = 1000000;

int cnt[V * 2];

int64 phi(int64 x) {return x * x; }

int main(int argc, char **argv) {
#ifndef ONLINE_JUDGE
     freopen("344.in" , "r", stdin);
     // freopen("344.out", "w", stdout);
#endif
     ios_base::sync_with_stdio(false);

     int n, x, t = 123456; int64 ans = 0;
     cin >> n;
     n = 1500;
     FOR (i, 1, n) {
         cin >> x;
         if (t & 1) t = (t >> 1) ^ 926252;
         else t >>= 1;
         x = t % 2048 + 1;
         // cerr << x << endl;
         FOR (j, -(x / 2), x / 2) {
             if (x % 2 == 1 || j != 0) {
                 insert(i + j);
             }
         }
         ans -= 1ll * i * i * x;
     }
     cerr << "-------" << endl;
     for (auto x : S) {
         cerr << x.car << " " << x.cdr << endl;
         FOR (i, x.car, x.cdr)
             ans += 1ll * i * i;
     }
     cerr << ans / 2 << endl;

     return 0; 
}
