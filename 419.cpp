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

vector<string> tab = {
    "1112", 
    "1112133", 
    "111213322112", 
    "111213322113", 
    "1113", 
    "11131", 
    "111311222112", 
    "111312", 
    "11131221", 
    "1113122112", 
    "1113122113", 
    "11131221131112", 
    "111312211312", 
    "11131221131211", 
    "111312211312113211", 
    "111312211312113221133211322112211213322112", 
    "111312211312113221133211322112211213322113", 
    "11131221131211322113322112", 
    "11131221133112", 
    "1113122113322113111221131221", 
    "11131221222112", 
    "111312212221121123222112", 
    "111312212221121123222113", 
    "11132", 
    "1113222", 
    "1113222112", 
    "1113222113", 
    "11133112", 
    "12", 
    "123222112", 
    "123222113", 
    "12322211331222113112211", 
    "13", 
    "131112", 
    "13112221133211322112211213322112", 
    "13112221133211322112211213322113", 
    "13122112", 
    "132", 
    "13211", 
    "132112", 
    "1321122112", 
    "132112211213322112", 
    "132112211213322113", 
    "132113", 
    "1321131112", 
    "13211312", 
    "1321132", 
    "13211321", 
    "132113212221", 
    "13211321222113222112", 
    "1321132122211322212221121123222112", 
    "1321132122211322212221121123222113", 
    "13211322211312113211", 
    "1321133112", 
    "1322112", 
    "1322113", 
    "13221133112", 
    "1322113312211", 
    "132211331222113112211", 
    "13221133122211332", 
    "22", 
    "3", 
    "3112", 
    "3112112", 
    "31121123222112", 
    "31121123222113", 
    "3112221", 
    "3113", 
    "311311", 
    "31131112", 
    "3113112211", 
    "3113112211322112", 
    "3113112211322112211213322112", 
    "3113112211322112211213322113", 
    "311311222", 
    "311311222112", 
    "311311222113", 
    "3113112221131112", 
    "311311222113111221", 
    "311311222113111221131221", 
    "31131122211311122113222", 
    "3113112221133112", 
    "311312", 
    "31132", 
    "311322113212221", 
    "311332", 
    "3113322112", 
    "3113322113", 
    "312", 
    "312211322212221121123222113", 
    "312211322212221121123222112", 
    "32112",
};

map<string, int> f;

string RLE(string s) {
    string t;
    int cnt = 0; char x = '0';
    s += '4';
    for (auto c : s) {
        if (c == x) ++cnt;
        else {
            if (cnt) {
                t += (char)(cnt + '0');
                t += x;
            }
            cnt = 1;
            x = c;
        }
    }
    return t;
}

const int n = 92;
int64 E = (int64)1e12 - 8;

typedef uint mat[n][n];

mat M, U;

void matmul(mat a, mat b, mat c) {
    mat t = {{0}};
    FOR (i, 0, n - 1) FOR (j, 0, n - 1) FOR (k, 0, n - 1)
        t[i][j] += a[i][k] * b[k][j];
    memcpy(c, t, sizeof(t));
}

bool dfs(string s, vector<int> &x) {
    if (s == "") return true;
    ROF (i, n - 1, 0) {
        if (s.substr(0, SZ(tab[i])) == tab[i]) {
            x.clear();
            if (dfs(s.substr(SZ(tab[i])), x)) {
                x.push_back(i);
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    FOR (i, 0, n - 1) {
        f[tab[i]] = i;
    }
    FOR (i, 0, n - 1) {
        string x = tab[i], y = RLE(x);
        // cerr << x << " " << y << endl;
        vector<int> v;
        assert(dfs(y, v));
        if (i == 81) v = {47 - 1, 33 - 1, 61 - 1, 29 - 1, 92 - 1};
        for (auto r : v)
            ++M[i][r];
    }
    FOR (i, 0, n - 1) {
        int cnt = 0;
        FOR (j, 0, n - 1)
            if (M[i][j])
                cerr << j + 1 << " ";
        cerr << endl;
        // if (cnt != 1) cerr << i << " " << cnt << endl;
    }
    // v[23] = v[38] = 1;
    U[23][23] = U[38][38] = 1;
    for (; E; E >>= 1, matmul(M, M, M))
        E & 1 ? matmul(U, M, U), 0 : 0;

    uint cnt[4] = {0};
    FOR (i, 0, n - 1) {
        uint w = 0;
        FOR (j, 0, n - 1)
            w += U[j][i];
        for (auto x : tab[i])
            cnt[x - '0'] += w;
    }
    const int mask = (1 << 30) - 1;
    cout << (cnt[1] & mask) << "," << (cnt[2] & mask) << "," << (cnt[3] & mask) << endl;

    return 0; 
}

// http://www.nathanieljohnston.com/2010/10/a-derivation-of-conways-degree-71-look-and-say-polynomial/
