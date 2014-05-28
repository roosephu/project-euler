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

const int LMT = 4e7, MOD = 1e9 + 7;
const int64 n = 1; // 96889010407ll;

#include <gmpxx.h>

typedef mpz_class ZZ;
int p[100];
map<ZZ, ZZ> f;
int prime[LMT + 10];
ZZ phi[LMT + 10];

ZZ prephi(ZZ n)
{
    if (n < LMT) return phi[n.get_si()];
    if (f.count(n)) return f[n];
    // cout << n << endl;
    ZZ &t = f[n];
    t = n * (n + 1) / 2;
    for (ZZ i = 2, j; i <= n; i = j) {
        j = n / (n / i) + 1;
        t -= (j - i) * prephi(n / i);
    }
    return t;
}

int64 C2(int64 x) {
    int64 a = x, b = x + 1;
    if (a & 1) b >>= 1; else a >>= 1;
    return (a % MOD) * (b % MOD) % MOD;
}

int64 to64(ZZ x) {
    ZZ a = (x >> 32);
    int64 ret = ((int64)a.get_ui() << 32) | x.get_ui();
    // cout << ret << " " << x << endl;
    return ret;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    for (int i = 2; i <= LMT; ++i) {
        if (!prime[i]) prime[++prime[0]] = i, phi[i] = i - 1;
        for (int j = 1, k = LMT / i, t; prime[j] <= k; ++j) {
            prime[t = i * prime[j]] = 1;
            if (i % prime[j]) phi[t] = phi[i] * phi[prime[j]];
            else {phi[t] = phi[i] * prime[j]; break; }
        }
    }
    phi[1] = 1;
    for (int i = 1; i <= LMT; ++i)
        phi[i] += phi[i - 1];

    auto gn = ZZ(1);
    for (int i = 1; i <= 13; ++i)
        gn *= 7;
    // gn = 343;
    
    ZZ s = 0, f = 1;
    for (ZZ i = 1, j; i <= gn; i = j) {
        j = gn / (gn / i) + 1;
        ZZ d = prephi(j - 1) - prephi(i - 1), u = ((gn / i + 1) % MOD), v = d % (MOD - 1);;
        if (i != 1) d *= 2, (v *= 2) %= (MOD - 1);
        assert(v >= 0);
        (f *= (int)fpm(u.get_si(), v.get_si(), MOD)) %= MOD;
        (s += (gn / i) % MOD * ((gn / i) % MOD) * d % MOD) %= MOD;
    } 
    cout << f << " " << s << endl;
    f = (gn + 1) % MOD * f % MOD;
    f = f * f % MOD;
    cout << f * (f - 4 * gn % MOD * ((gn + 1) % MOD) % MOD + MOD) % MOD + 2 * (s + gn % MOD * (gn % MOD)) % MOD - 1 << endl;

    for (int n = 1; n <= 10; ++n) {
        memset(p, 0, sizeof(p));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (gcd(i, j) == 1)
                    ++p[n / max(i, j)];
            }
        }
        

        int64 f = 1, s = 0;
        for (int i = 1; i <= n; ++i)
            f *= fpm(i + 1, p[i], inf), s += i * i * p[i];
        cout << f << " " << s << endl;
        f *= n + 1;
        f *= f;
        // cout << f * (f - 4 * n * (n + 1)) - 1 + 2 * (s + n * n) << endl;
    }

    return 0; 
}


