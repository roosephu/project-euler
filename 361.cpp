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

const int MOD = 1e9;

int e[65536];
uint Q[142963561], d = 0;
// int Q[65536], cnt[100];

void dfs(int dep, int now) {
    if (dep == 0) return (void)(Q[d++] = now);
    dfs(dep - 1,  now);
    dfs(dep - 1, !now);
}

// string bin(int64 x) {
//     string t;
//     for (; x; x >>= 1)
//         t = (char)('0' + x % 2) + t;
//     return t;
// }

#define E __builtin_parity
#define TE(x,y) (E((x) + (y)) ^ E(x) ^ 1)

// int E(uint32 x) {
//     return e[x >> 16] ^ e[x & 0xFFFF];
// }

int Five(uint x) {
    int s = 0, t = !E(x);
    for (int i = 0; i < 8; ++i)
        s = s * 2 + (E(x + i) ^ t);
    return s;
}

bool cmp(uint x, uint y) {
    int p = !E(x), q = !E(y);
    for (; ~(x ^ y) & 1; )
        x >>= 1, y >>= 1;
    for ( ; ; ) {
        int s = E(x), t = E(y);
        if ((p ^ s) != (q ^ t)) return (p ^ s) < (q ^ t);
        ++x, ++y;
    }
    return 0;
}

int64 get(uint x, int n) {
    int t = !E(x); int64 ret = 0;
    for (int i = 0; i < n; ++i) {
        ret = ret * 2 + (t ^ E(x + i));
        if (ret > MOD) ret -= MOD;
    }
    return ret;
}

// [0, A), [B, C), [D, E)
int64 query(int64 N) {
    N -= 1 + 2 + 3 + 5 + 6 + 8;
    int64 n = 6, L = 8, A = 6, B = 7, C = 8, D = 11, E = 12;
    for (; ; ) {
        ++n;
        if (A == B && C == D) {
            A = E;
            C = E / 3 * 4, B = C - 1;
            E <<= 1, D = E - 1;
            L += 2;
        } else {
            if (A < B) --B, ++L;
            if (C < D) --D, ++L;
        }
        if (L >= N) break;
        N -=L;
    }

    int cnt[256] = {0};
    for (int64 i = 0; i < A; ++i) ++cnt[Five(i)];
    for (int64 i = B; i < C; ++i) ++cnt[Five(i)];
    for (int64 i = D; i < E; ++i) ++cnt[Five(i)];

    int S = 0;
    for (int i = 0; i < 256; ++i) {
        S = i;
        if (cnt[i] >= N) break;
        N -= cnt[i];
    }

    int t = 0;
    for (int i = 0; i < A; ++i) if (Five(i) == S) Q[t++] = i;
    for (int i = B; i < C; ++i) if (Five(i) == S) Q[t++] = i;
    for (int i = D; i < E; ++i) if (Five(i) == S) Q[t++] = i;

    nth_element(Q, Q + N - 1, Q + t, cmp);
    // sort(Q, Q + t, cmp);
    // for (int i = 0; i < t; ++i)
    //     for (int j = i + 1; j < t; ++j)
    //         cout << Q[i] << " " << Q[j] << " " << cmp(Q[i], Q[j]) << endl;

    int64 ans = 0; 
    // for (int i = 0; i < t; ++i)
    //     cout << get(Q[i], n) << endl;
    ans = get(Q[N - 1], n);
    // for (int i = 0; i < n - 1; ++i)
    //     ans = ans * 2 + (::E(pos + i) ^ w);
    
    cout << n << " " << t << " " << ans << endl;
    // cout << n << " " << L << " " << A << " " << B << " " << C << " " << D << " " << E << endl;
    return ans;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    for (int i = 1; i < 65536; ++i)
        e[i] = e[i >> 1] ^ (i & 1);

    int64 n = 100, ans = 12;
    for (int i = 2; i <= 18; ++i) {
        ans += query(n);
        n *= 10;
    }
    cout << ans % MOD << endl;
    
    // dfs(16, 0);
    // // for (int i = 0; i < 65530; ++i)
    // //     assert(E(i) == Q[i]);
    // cout << get(8, 13) << " " << get(12, 13) << endl;

    // int L = 1;
    // set<int64> S;
    // for (int i = 1; i <= 60; ++i) {
    //     if (L < i) L *= 2;
    //     set<int> T;
    //     for (int j = 0; j <= L * 2; ++j) {
    //         int64 s = get(j, i);
    //         if (S.count(s)) {
    //             // cout << i << " " << bin(s) << endl;
    //         } else
    //             T.insert(j);
    //         S.insert(s);
    //     }
    //     cout << i << ":";
    //     for (auto x : T) {
    //         cout << " " << x;
    //     }
    //     cout << endl;
    //     // cnt[i] = SZ(T);
    //     // if (i > 3) assert(cnt[i] == cnt[i / 2 + 1] + cnt[(i + 1) / 2]);
    // }
    // cout << SZ(S) << endl;
    // // for (auto x : S) {
    // //     cout << x << endl;
    // // }
    
    return 0; 
}

