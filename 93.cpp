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

set<int> S;

void dfs(vector<double> v) {
    int t = SZ(v);
    if (t == 1) {
        int k = v[0] + 1e-5;
        if (abs(k - v[0]) <= 1e-4)
            S.insert(v[0]);
        return ;
    }
    for (int i = 0; i < t; ++i)
        for (int j = 0; j < t; ++j)
            if (i != j) {
                vector<double> x;
                for (int k = 0; k < t; ++k)
                    if (k != i && k != j)
                        x.push_back(v[k]);

                double p = v[i], q = v[j];
                if (p <= q) { auto A = x; A.push_back(p + q); dfs(A); }
                if (p >  q) { auto B = x; B.push_back(p - q); dfs(B); }
                if (p <= q) { auto C = x; C.push_back(p * q); dfs(C); }
                if (     q) { auto D = x; D.push_back(1.0 * p / q); dfs(D); }
            }
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    
    int mx = 0, L = 9;
    for (int a = 1; a <= L; ++a)
        for (int b = a + 1; b <= L; ++b)
            for (int c = b + 1; c <= L; ++c)
                for (int d = c + 1; d <= L; ++d) {
                    S.clear();
                    vector<double> v = {a, b, c, d};
                    dfs(v);

                    int n = 1;
                    for (; S.count(n); ++n)
                        ;
                    if (n > mx) {
                        mx = n;
                        cout << SZ(S) << " " << mx << " " << a << b << c << d << endl;
                    }
                }

    return 0; 
}
