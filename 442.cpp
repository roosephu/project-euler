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
#include <gmpxx.h>
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
typedef mpz_class ZZ;

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

const int MAXBUF = 10000, LMT = 22;

struct node;
node *jump(node *, int);

struct node {
    node *c[10], *x[10], *fail;
    bool flag;
    ZZ cnt[LMT];

    node *operator[](size_t x) {
        return jump(this, x);
    }
} ;


node buf[MAXBUF], *bptr = buf, *root;

node *get_new() {
    node *p = ++bptr;
    FOR (i, 0, LMT - 1) p->cnt[i] = -1;
    return p;
}

void insert(string S) {
    node *t = root;
    FOR (i, 0, SZ(S) - 1) {
        int c = S[i] - '0';
        if (!t->c[c]) t->c[c] = get_new();
        t = t->c[c];
    }
    t->flag = true;
}

void build_AC() {
    queue<node *> Q; Q.push(root); root->fail = root;
    for (; !Q.empty(); Q.pop()) {
        node *x = Q.front();
        FOR (i, 0, 9) {
            node *c = x->c[i];
            if (!c) continue;
            c->fail = x == root ? root : jump(x->fail, i);
            c->flag |= c->fail->flag;
            Q.push(c);
        }
    }
}

ZZ &count(node *t, int x) {
    auto &ret = t->cnt[x];
    if (ret != -1) return ret;
    if (t->flag) return ret = 0;
    if (x == 0) return ret = 1;
    ret = 0;
    FOR (i, 0, 9) {
        ret += count(jump(t, i), x - 1);
    }
    return ret;
}

node *jump(node *x, int c) {
    for (; x != root && !x->c[c]; x = x->fail)
        ;
    if (x->c[c]) x = x->c[c];
    return x;
}

void init() {
    
    root = get_new();
    mpz_class t = 1;
    FOR (i, 1, 30) {
        t *= 11;
        insert(t.get_str());
        cerr << t << endl;
    }
    build_AC();
    for (node *p = buf + 1; p <= bptr; ++p) {
        FOR (i, 0, LMT - 1) {
            count(p, i);
        }
    }

    node *p = root->c[2], *q = root->c[3];
    ROF (i, 5, 0) {
        FOR (x, 0, 9) {
            if (jump(p, x)->cnt[i] != jump(q, x)->cnt[i]) {
                cerr << i << " " << x << " " << p << " " << q << " " << root << endl;
                p = jump(p, x), q = jump(q, x);
            }
        }
    }
    // node *x = root[2][8][5][3][1][1], *y = root[3][8][5][3][1][1];
    // cerr << x->cnt[0] << " " << y->cnt[0] << endl;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    init();
    ZZ upb = 1e18, ans = 0;

    node *t = root;
    ROF (len, LMT - 1, 0) {
        FOR (i, 0, 9) {
            node *p = jump(t, i);
            cerr << len << " " << i << " " << p->cnt[len] << endl;
            if (p->cnt[len] <= upb) {
                upb -= p->cnt[len];
            } else {
                t = p;
                ans = ans * 10 + i;
                break;
            }
        }
        // cout << ans << " " << upb << endl;
    }
    cout << ans << endl;

    return 0; 
}
