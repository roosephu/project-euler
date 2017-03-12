#include "fmt/format.h"
#include <NTL/ZZ.h>
using namespace fmt;
using namespace NTL;

namespace PE586 {
    const long N = 1e15;
    const int LMT = 1e7;
    const int MAX_SQUARE = 3.2e7;

    int primes[LMT], check[LMT];
    int cnt[MAX_SQUARE];
    long ans = 0, test = 0;

    void dfs1(int depth, long v) {
        ++cnt[v];
        for (int i = depth; i <= primes[0]; ++i) {
            int p = primes[i];
            if (v * p * p > MAX_SQUARE) break;
            if (p % 5 == 1 || p % 5 == 4) continue;
            for (long u = v * p * p; u <= MAX_SQUARE; u *= p * p) {
                dfs1(i + 1, u);
            }
        }
    }

    bool feasible(int n, int p) {
        for (int i = 1; primes[i] <= p; ++i) {
            while (n % primes[i] == 0) {
                n /= primes[i];
            }
        }
        return n == 1;
    }

    void dfs2(int rem, int last_exp, long last_val, int last_idx) {
        ++test;
        if (test % 10000000 == 0)
            print("test = {}\n", test);
        if (rem == 1)
            ans += cnt[last_val];

        for (int e = 2; e <= last_exp; ++e) {
            if (rem % e != 0 || !feasible(rem, e)) continue;
            // print("{} {}\n", rem, last_exp, last_val);
            for (int i = 1; i <= primes[0]; ++i) {
                if (e == last_exp && i >= last_idx)
                    break;
                int p = primes[i];
                if (p % 5 != 1 && p % 5 != 4) continue;
                long val = last_val;
                for (int t = 1; t < e; ++t)
                    val /= p;
                if (val) {
                    if (check[i]) continue;
                    check[i] = 1;
                    dfs2(rem / e, e, val, i);
                    check[i] = 0;
                } else {
                    break;
                }
            }
        }
    }

    void main() {
        PrimeSeq gen;
        for (int u; (u = gen.next()) <= LMT; )
            primes[++primes[0]] = u;
        print("#primes = {}\n", primes[0]);
        dfs1(1, 1);
        dfs1(1, 5);
        print("initialized\n");
        for (int i = 1; i < MAX_SQUARE; ++i)
            cnt[i] += cnt[i - 1];
        dfs2(80, 80, N, 0);
        test = 0;
        dfs2(81, 81, N, 0);
        print("ans = {}\n", ans);
    }
}

int main() {
    PE586::main();
    return 0;
}