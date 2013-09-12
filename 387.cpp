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
    Graph(int n) {adj.clear(); adj.resize(n + 5);}
    Graph() {adj.clear(); }
    void resize(int n) {adj.resize(n + 5); }
    void add(int s, edge e){adj[s].push_back(e);}
    void del(int s, edge e) {adj[s].erase(find(iter(adj[s]), e)); }
    vector<edge>& operator [](int t) {return adj[t];}
};

const int64 N = 1e14, LMT = 1e4;

int cnt = 0;
int prime[LMT + 1];

bool isP(int64 x) {
    if (x == 1) return false;
    int i = 1;
    for (; i <= prime[0] && prime[i] * prime[i] <= x; ++i) {
        if (x % prime[i] == 0) return false;
    }
    if (i <= prime[0]) return true;
    
    char s[100];
    sprintf(s, "factor %lld > tmp", x);
    system(s);
    FILE *fin = fopen("tmp", "r");
    
    int n = 0; int64 a[50];
    fscanf(fin, "%*lld%*c");
    for (; fscanf(fin, "%lld", &a[n]) == 1; ++n);
    fclose(fin);
    return n == 1;
}

int64 ans = 0;
void search(int64 n, int s) {
    if (n >= N) return ;
    if (n % s != 0) return ;
    ++cnt;
    if (n * 10 < N && n >= 10 && isP(n / s)) {
        FOR (i, 0, 9) {
            if (isP(n * 10 + i))
                ans += n * 10 + i;
        }
    }
    // cerr << n << endl;
    FOR (i, 0, 9) {
        search(n * 10 + i, s + i);
    }
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    FOR (i, 2, LMT) {
        if (!prime[i]) prime[++prime[0]] = i;
        for (int j = 1, k = LMT / i; prime[j] <= k; ++j) {
            prime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    
    FOR (i, 1, 9) search(i, i);

    cerr << cnt << " " << ans << endl;
    // cerr << isP(1000000000131ll) << endl;
    return 0; 
}
