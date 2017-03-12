#include "fmt/format.h"
#include <NTL/ZZ.h>
using namespace fmt;
using namespace NTL;

namespace PE590 {
    const int MOD = 1e9, PHI = 4e8, NUM_PRIMES = 20000, LMT = 50000;

    int cnt[20];
    long cb[NUM_PRIMES + 1][NUM_PRIMES + 1];
    long ans = 0;

    int coef(int n, int p) {
        int e = 0;
        for (; n; n /= p)
            ++e;
        return e;
    }

    void dfs(int depth, long exp, long coef) {
        if (depth == 0) {
            ans += coef * PowerMod(2, exp, MOD) % MOD;
            return;
        }
        int t = cnt[depth];
        if (t == 0)
            return dfs(depth - 1, exp, coef);
        for (int i = 0; i <= t; ++i) {
            dfs(depth - 1,
                exp * PowerMod(depth - 1, i, PHI) % PHI * PowerMod(depth, t - i, PHI) % PHI,
                coef * cb[t][i] % MOD * PowerMod(MOD - 1, i, MOD) % MOD);
        }
    }

    void main() {
        PrimeSeq gen;
        for (int u; u = gen.next(), u <= LMT; )
            ++cnt[coef(LMT, u)];
        for (int i = 0; i <= 20; ++i)
            print("{} ", cnt[i]);
        print("\n");

        for (int i = 0; i < NUM_PRIMES; ++i)
            for (int j = 0; j <= i; ++j)
                cb[i][j] = j ? (cb[i - 1][j - 1] + cb[i - 1][j]) % MOD : 1;
        ans = 0;
        dfs(16, 1, 1);
        print("ans = {}\n", ans % MOD);
    }
}

int main() {
    PE590::main();
    return 0;
}