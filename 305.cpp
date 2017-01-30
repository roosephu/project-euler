#include "fmt/format.h"
#include "fmt/ostream.h"
#include <tuple>
#include <map>
using namespace fmt;
using namespace std;

const int M = 10;

int size;

struct Perm {
    int x[M], y[M];

    pair<int, long> apply(int state) {
        return {x[state], y[state]};
    }
};

Perm operator + (Perm a, Perm b) {
    Perm c;
    for (int i = 0; i <= size; ++i) {
        c.x[i] = b.x[a.x[i]];
        c.y[i] = a.y[i] + b.y[a.x[i]];
    }
    return c;
}

bool operator < (Perm a, Perm b) {
    for (int i = 0; i <= size; ++i) {
        if (a.x[i] != b.x[i])
            return a.x[i] < b.x[i];
        if (a.y[i] != b.y[i])
            return a.y[i] < b.y[i];
    }
    return false;
}

Perm digits[100];
map<tuple<int, Perm, int>, pair<int, long>> f;

pair<int, long> dfs(int h, Perm perm, int state) {
    if (h == 0) return perm.apply(state);
    tuple<int, Perm, int> S = {h, perm, state};
    if (!f.count(S)) {
        long ret = 0;
        for (int i = 0; i <= 9; ++i) {
            auto p = dfs(h - 1, perm + digits[i], state);
            state = p.first;
            ret += p.second;
        }
        f[S] = {state, ret};
    }
    return f[S];

}

template<class X, class Y> ostream& operator << (ostream& s, const pair<X, Y>& p) {
	return s << "(" << p.first << ", " << p.second << ')';
}

long calc(long v, long count) {
    int s[M], next[M], remain[M];
    int n = 0;

    for (; v; v /= 10)
        s[++n] = v % 10;
    s[n + 1] = -1;

    for (int i = 1, j = n; i < j; ++i, --j) {
        swap(s[i], s[j]);
    }

    next[0] = -1, next[1] = 0;
    for (int i = 2, j = 0; i <= n; ++i) {
        while (j >= 0 && s[j + 1] != s[i])
            j = next[j];
        next[i] = ++j;
    }

    size = n;
    // print("size = {}, value = {}\n", n, count);
    for (int c = 0; c <= 9; ++c) {
        for (int i = 0; i <= n; ++i) {
            int x = i;
            while (x >= 0 && s[x + 1] != c)
                x = next[x];
            digits[c].x[i] = ++x;
            digits[c].y[i] = x == n;
        }
    }

    f.clear();
    Perm prefix;
    for (int i = 0; i <= size; ++i) {
        prefix.x[i] = i;
        prefix.y[i] = 0;
    }

    // print("ans: {}\n", dfs(3, prefix, 0).second);
    // return 0;

    int len = 0, state = 0;
    long ans = 0, subtree = 1;
    for (bool done = false; !done; ) {
        ++len;
        subtree *= 10;
        for (int c = 1; c <= 9; ++c) {
            auto p = dfs(len - 1, prefix + digits[c], state);
            // print("length: {}, start: {}, count: {}\n", len, c, p.second);
            if (p.second >= count) {
                prefix = prefix + digits[c];
                remain[len] = c;
                done = true;
                break;
            }
            count -= p.second;
            state = p.first;
            ans += len * subtree / 10;
        }
    }
    for (int i = len - 1; i; --i) {
        subtree /= 10;
        for (int c = 0; c <= 9; ++c) {
            auto p = dfs(i - 1, prefix + digits[c], state);
            // print("pos: {}, start: {}, count: {}, subtree = {}\n", i, c, p.second, subtree);
            if (p.second >= count) {
                prefix = prefix + digits[c];
                remain[i] = c;
                // print("digit: {}\n", c);
                break;
            }
            count -= p.second;
            state = p.first;
            ans += len * subtree / 10;
        }
    }
    for (int i = len; i; --i) {
        ++ans;
        int c = remain[i];
        auto p = digits[c].apply(state);
        state = p.first;
        if (p.second == 1) {
            break;
        }
    }

    return ans - n + 1;
}

int main() {
    // print("{}\n", calc(7780, 7780));
    // print("{}\n", calc(12, 12));
    long v = 1, ans = 0;
    for (int i = 1; i <= 10000; ++i)
        ans += calc(i, i);
    // for (int e = 1; e <= 13; ++e) {
    //     v *= 3;
    //     ans += calc(v, v);
    // }
    print("ans = {}\n", ans);
    return 0;
}