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

struct node {                   // (x + y sqrt{5}) / 2
    int64 x, y;
} ;

node operator * (node a, node b) {
    return (node){(a.x * b.x + 5 * a.y * b.y) / 2, (a.x * b.y + a.y * b.x) / 2};
}

node operator + (node a, node b) {
    return (node){a.x + b.x, a.y + b.y};
}

const int N = 56;
const double s5 = sqrt(5);
const int64 n = 1e10, LMT = (n + 10) * 2;

node f[N];

long long ans;
int cnt;

void dfs(node now, int x) {
    // if (now.x + now.y * s5 >= LMT) return ;
    // if (x >= N) {
    //     if (now.y == 0 && now.x / 2 <= n) {
    //         // cout << now.x / 2 << endl;
    //         ++cnt;
    //         ans += now.x / 2;
    //     }
    //     return ;
    // }
    // dfs(now + f[x], x + 2);
    // dfs(now       , x + 1);
    if (now.y == 0) {
        ++cnt;
        ans += now.x / 2;
    }
    for (int i = x; i < N; ++i) {
        node v = now + f[i];
        if (v.x + v.y * s5 >= LMT) return ;
        dfs(v, i + 2);
    }
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    f[0] = (node){2, 0};
    node a = (node){2, 0}, b = (node){-1, 1};
    for (int i = 1; i < N; ++i) {
        a = a * (node){1, 1};
        b = b * (node){-1, 1};
        f[i] = a + b;
        cout << f[i].x << " " << f[i].y << endl;
        // if (f[i].x + s5 * f[i].y >= LMT) {
        //     cout << i << " " << endl;
        //     break;
        // }
    }
    dfs((node){0, 0}, 1);
    cout << "ans: " << ans + 1 << endl;
    cout << "cnt: " << cnt << endl;

    return 0; 
}

