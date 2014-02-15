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
#define fst first
#define snd second
#define PB push_back
#define MKP make_pair
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
template <typename T> T gcd(T x, T y) {
    for (T t; x; t = x, x = y % x, y = t)
        ;
    return y;
}

template<class edge> struct Graph {
    vector<vector<edge> > adj;
    Graph(int n) {adj.clear(); adj.resize(n + 5);}
    Graph() {adj.clear(); }
    void resize(int n) {adj.resize(n + 5); }
    void add(int s, edge e){adj[s].push_back(e);}
    void del(int s, edge e) {adj[s].erase(find(iter(adj[s]), e)); }
    vector<edge>& operator [](int t) {return adj[t];}
};

const int N = 4;

vector<pair<int, int>> vec;
pair<int, int> f[1 << N];

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    FOR (i, 1, N) {
        vec.push_back(make_pair(1 << (i - 1), i + 1));
    }
    FOR (i, 1, N * 2) {
        FOR (j, 1, (i * i - 1) / 4) {
            double x = sqrt(i * i - 4 * j);
            if (sqr(int(x)) == i * i - 4 * j) continue;
            int a = (i + x) / 2, b = (i - x) / 2;
            if (a > N || b < 1) continue;
            vec.PB(MKP(1 << (a - 1) | 1 << (b - 1), 1 + i + j));
        }
    }
    f[0] = MKP(1, 1);

    const int mask = (1 << N) - 1;
    FOR (S, 0, mask) {
        int x = __builtin_ctz(~S);
        for (auto p : vec) {
            if ((S & p.fst) == 0 && (p.fst >> x & 1) == 1) {
                f[S | p.fst].fst += f[S].fst * p.snd;
                f[S | p.fst].snd += f[S].snd;
            }
        }
    }
    cerr << f[mask].fst - f[mask].snd << " " << f[mask].fst << " " << f[mask].snd << endl;

    return 0; 
}
