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
#define car first
#define cdr second
#define PB push_back
#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
#define For(i, a, b) for (int _end_ = (b), i = (a); i <= _end_; ++i)
#define Rof(i, a, b) for (int _end_ = (b), i = (a); i >= _end_; --i)
#define FOR(i, a, b) for (int _end_ = (b), i = (a); i != _end_; ++i)
#define ROF(i, a, b) for (int _end_ = (b), i = (a); i != _end_; --i)

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
    Graph(int n) {adj.clear(); adj.resize(n + 5);}
    Graph() {adj.clear(); }
    void resize(int n) {adj.resize(n + 5); }
    void add(int s, edge e){adj[s].push_back(e);}
    void del(int s, edge e) {adj[s].erase(find(iter(adj[s]), e)); }
    vector<edge>& operator [](int t) {return adj[t];}
};

map<int, int64> f, g;

#define strip(S,x) ((S) >> ((x) << 1) & 3)
#define gen(x,d) ((x) << ((d) << 1))
#define CR(d,s) ((d) == n - 1 ? ((s) << 2) : (s))

const int n = 10;

string show(int x) {
    string t = ""; char tab[] = {'#', '(', ')'};
    FOR (i, 0, n + 1) t += tab[strip(x, i)];
    return t;
}

void push(int row, int state, int64 cnt) {
    // cerr << "  -> " << show(state) << endl;
    if (row != n - 1 || strip(state, n) == 0)
        g[CR(row, state)] += cnt;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    const int delta[] = {0, 1, -1};
    g[0] = 1;
    FOR (i, 0, n) {
        FOR (j, 0, n) {
            cerr << "-----" << i << " " << j << endl;
            f = g, g.clear();
            for (auto _ : f) {
                int S = _.car; int64 cnt = _.cdr;
                int x = strip(S, j), y = strip(S, j + 1);
                // cerr << "     " << show(S) << " " << cnt << endl;
                
                if (x == 0 && y == 0) {
                    push(j, S | gen(1, j) | gen(2, j + 1), cnt);
                } else if (x == 2 && y == 1) {
                    push(j, S ^ gen(x, j) ^ gen(y, j + 1), cnt);
                } else if (x == 1 && y == 2) {
                    push(j, S ^ gen(x, j) ^ gen(y, j + 1), cnt * 2);
                } else if ((x != 0) ^ (y != 0)) {
                    push(j, S, cnt);
                    push(j, S ^ gen(x ^ y, j) ^ gen(x ^ y, j + 1), cnt);
                } else if (x == 1 && y == 1) {
                    int cur = S ^ gen(x, j) ^ gen(y, j + 1), b = 1;
                    FOR (k, j + 2, oo) {
                        if (!(b += delta[strip(S, k)])) {
                            cur = cur ^ gen(3, k);
                            break;
                        }
                    }
                    push(j, cur, cnt);
                } else if (x == 2 && y == 2) {
                    int cur = S ^ gen(x, j) ^ gen(y, j + 1), b = -1;
                    ROF (k, j - 1, -1) {
                        if (!(b += delta[strip(S, k)])) {
                            cur = cur ^ gen(3, k);
                            break;
                        }
                    }
                    push(j, cur, cnt);
                }
            }
        }
    }
    cerr << g[0] << endl;

    return 0; 
}

