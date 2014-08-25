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
#include <initializer_list>
#include <unordered_map>
#include <unordered_set>

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

const int N = 9765625, MOD = 60060 * 5;

bool f[MOD];
set<tuple<int, int, int>> F;

int64 calc(int N) {
    F.clear();
    cout << N << endl;
    int64 ret = 0;
    for (int m = 0; m * m <= N; ++m) {
        // cout << m << endl;
        for (int n = 0; m * m + n * n <= N; ++n) {
            for (int p = 0; m * m + n * n + p * p <= N; ++p) {
                int k = N - (m * m + n * n + p * p);
                if (!f[k % MOD]) continue;
                int q = sqrt(k);
                if (q * q == k && (m + n + p + q) % 2 == 1) {
                    int a = m * m + n * n - p * p - q * q; if (a < 0) continue;
                    int b = 2 * (m * q + n * p); if (b == 0 && a != 1) continue;
                    int c = 2 * (n * q - m * p); c = abs(c);
                    if (gcd(gcd(a, b), c) != 1) continue;
                    if (a > b) swap(a, b); if (b > c) swap(b, c); if (a > b) swap(a, b);

                    auto x = tuple<int, int, int>(a, b, c);
                    if (F.count(x)) continue;
                    F.insert(x);
                    int w = a + b + c;
                    if (!(a >= 0 && b >= 0 && c >= 0)) continue;
                    if (a != 0) w *= 2;
                    if (b != 0) w *= 2;
                    if (c != 0) w *= 2;
                    if (a == b && b == c) w *= 1;
                    else if (a != b && b != c) w *= 6;
                    else w *= 3;
                    ret += w;
                    // cout << a << " " << b << " " << c << " " << N << " " << m << " " << n << " " << p << " " << q << endl;
                }
            }
        }
    }
    cout << "F: " << F.size() << endl;
    return ret;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    int64 ans = 0;
    for (int i = 0; i < MOD; ++i) f[(int64)i * i % MOD] = 1;

    int t = 0;
    for (int i = 0; i < MOD; ++i) t += f[i];
    cout << t << " " << MOD << endl;

    for (int i = 1; i <= N; ++i)
        if (N % i == 0)
            ans += calc(i) * (N / i);
    
    cout << (ans << 10) << endl;

    return 0; 
}

