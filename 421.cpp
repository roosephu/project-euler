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

const int M = 100000000;
const int64 N = 1e11;

bool b[M + 1];

vector<int> get_primes(int n)
{
	vector<int> P;

	FOR (i, 2, n) {
		if (!b[i]) P.push_back(i);
		int k = n / i;
		for (auto x : P) {
			if (x > k) break;
			b[x * i] = true;
			if (i % x == 0) break;
		}
	}
	return P;
}
auto primes = get_primes(M);

int find_root(int p) {
    int x = p - 1; vector<int> v;
    for (auto &y : primes) {
        if (x == 1) break;
        if (y * y > x) break;
        if (x % y == 0) {
            v.push_back((p - 1) / y);
            for (; x /= y, x % y == 0; );
        }
    }
    if (x != 1) v.push_back((p - 1) / x);
    x = p - 1;
    FOR (i, 2, p) {
        bool b = true;
        for (auto y : v)
            if (fpm(i, y, p) == 1) {
                b = false;
                break;
            }
        if (b) return i;
    }
    return -1;
}

int inv[15];

int main(int argc, char **argv) {
     ios_base::sync_with_stdio(false);

     int64 ans = 0; int cnt = 0;
     FOR (i, 1, 15) {
         int g = gcd(i, 15), x = i / g, y = 15 / g, e = 1;
         for (; y * e % x != 1 % x; ++e);
         inv[i % 15] = e;
     }
     for (auto p : primes) {
         int x = find_root(p);
         if (++cnt % 100000 == 0)
             cerr << p << " " << x << endl;
         int g = gcd(p - 1, 15), y = (p - 1) / g;
         int64 b = fpm(x, (p - 1) / (2 * g) * inv[(p - 1) % 15] % y, p), m = fpm(x, y, p);
         FOR (t, 1, g) {
             ans += (N + p - b) / p * p;
             b = b * m % p;
         }
     }
     cout << ans << endl;

     return 0; 
}

