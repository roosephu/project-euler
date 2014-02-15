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

bool chk(int64 x) {
    int64 y = sqrt(x);
    return y * y == x;
}

void get() {
long long a, b, c, d, e, f;
bool solved = false;
long long result = 0;

for (long long i = 4; !solved; i++) {
    a = i * i;
    for (long long j = 3; j < i && !solved; j++) {
        c = j * j;
        f = a - c;
        if (f <= 0 || !chk(f)) continue;

        long long kstart = (j % 2 == 1) ? 1 : 2;
        for (long long k = kstart; k < j; k += 2) {
            d = k * k;
            e = a - d;
            b = c - e;

            if (b <= 0 || e <= 0 || !chk(b) || !chk(e)) continue;

            long long x = (d + c) / 2;
            long long y = (e + f) / 2;
            long long z = (c - d) / 2;

            result = x + y + z;
            cout << result << " " << x << " " << y << " " << z << " " << sqrt(x - y) << " " << sqrt(y - z) << " " << sqrt(y + z) << endl;
            return ;
        }
    }
}
}

int main(int argc, char **argv) {
    get();
    ios_base::sync_with_stdio(false);
    for (int64 a = 1; a <= 10000; a += 2) {
        vector<int64> v;
        for (int x = 1; x * x < a; ++x) {
            if (a % x == 0) {
                int64 y = a / x;
                for (int t = 1; t * t <= y; ++t)
                    if (y % t == 0) {
                        int64 xx = x, yy = y / t;
                        if (yy > xx)
                        v.push_back(t * (yy + xx) * (yy - xx) / 2);

                        int64 tt = y / t;
                        xx = x, yy = y / tt;
                        if (yy > xx)
                        v.push_back(tt * (yy + xx) * (yy - xx) / 2);
                    }
            }
        }
        sort(ALL(v));
        v.resize(unique(ALL(v)) - v.begin());
        for (auto b : v)
            for (auto c : v)
                if (c > b && chk(a * a + b * b + c * c)) {
                    int64 z = (c * c - b * b) / 2;
                    int64 y = z + b * b;
                    int64 x = y + a * a;
                    cout << x + y + z << " " << x << " " << y << " " << z << " " << a << " " << b << " " << c << endl;
                }
    }

    return 0; 
}
