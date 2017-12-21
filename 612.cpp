#include "fmt/format.h"
#include <NTL/ZZ.h>
using namespace fmt;
using namespace NTL;

namespace PE612 {
    const long MOD = 1000267129 * 2;
    const int n = 18, m = 10;

    long f[1 << m];

    int popcnt(int S) {
        return S ? popcnt(S & (S - 1)) + 1 : 0;
    }

    void main() {
        for (int S = 0; S < (1 << m); ++S) {
            int p = popcnt(S);
            f[S] = 0;
            for (int i = 1; i <= n; ++i) {
                if (S & 1) { // contains 0
                    f[S] += (p - 1) * PowerMod(p, i - 1, MOD);
                } else {
                    f[S] += PowerMod(p, i, MOD);
                }
            }
            f[S] %= MOD;
        }
        for (int S = 0; S < (1 << m); ++S) {
            for (int T = S; T = (T - 1) & S; ) {
                f[S] = (f[S] + MOD - f[T]) % MOD;
            }
            // print("S = {}, f = {}\n", S, f[S]);
        }

        long ans = 0;
        for (int S = 0; S < (1 << m); ++S) {
            for (int T = 0; T < (1 << m); ++T) {
                if (S & T) {
                    ans += f[S] * f[T] % MOD;
                }
            }
        }
        ans = (ans + MOD - (PowerMod(m, n, MOD) - 1)) % MOD;
        // ans = ans * PowerMod(2, MOD - 2, MOD) % MOD;
        print("ans = {}\n", ans / 2);
    }
}

int main() {
    PE612::main();
    return 0;
}
