#include "fmt/format.h"
using namespace fmt;

const int whole = (1 << 10) - 2;

int translate(long n) {
    if (n < 0)
        return -1;
    int S = 0;
    for (; n; n /= 10) {
        int d = n % 10;
        if (S >> d & 1)
            return -1;
        S |= 1 << d;
    }
    return S;
}

int cnt = 0;
long mx = 0;

void dfs2(int dep, int S, int d, long x, int T, long concat) {
    if (S == 0 && x == 0) {
        if (dep >= 2 && T == (1 << 10) - 1) {
            if (concat > mx) {
                mx = concat;
                print("mx = {}\n", mx);
            }
            cnt += 1;
            if (cnt % 100 == 0)
                print("d = {}, concat = {}\n", d, concat);
        }
        return;
    }
    if (x != 0) {
        long prod = d * x, p = translate(prod);
        if (p > 0 && (p & T) == 0) {
            long power = 1;
            while (power <= prod)
                power *= 10;

            // if (d == 6 && x == 1273)
                // print("S = {:b}, p = {}, concat = {}\n", S, p, concat * power + prod);
            dfs2(dep + 1, S, d, 0, T | p, concat * power + prod);
        }
    }

    for (int i = x == 0; i <= 9; ++i)
        if (S >> i & 1) {
            dfs2(dep, S ^ (1 << i), d, x * 10 + i, T, concat);
        }
}

void dfs1(int S, int d) {
    if (d > 100)
        return;
    print("d = {}\n", d);
    if (d != 0)
        dfs2(0, S, d, 0, 0, 0);
    for (int i = d == 0; i <= 9; ++i)
        if (S >> i & 1) {
            dfs1(S ^ (1 << i), d * 10 + i);
        }
}

int main() {
    dfs1((1 << 10) - 1, 0);
    return 0;
}