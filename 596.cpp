#include "fmt/format.h"
using namespace fmt;

namespace PE596 {
    const long n = 100000000; // N = n + 10;
    const int MOD = 1000000007, inv2 = (MOD + 1) / 2;

    // int f[N];

    // void bf() {
    //     for (int x = 0; x * x <= n; ++x) {
    //         for (int y = 0; x * x + y * y <= n; ++y) {
    //             f[x * x + y * y] += (1 + !!x) * (1 + !!y);
    //         }
    //     }
    //     for (int i = 1; i <= n; ++i)
    //         f[i] += f[i - 1];

    //     long ans = 0;
    //     for (int i = 0; i <= n; ++i) {
    //         ans += (long) (f[i] - (i ? f[i - 1] : 0)) * f[n - i];
    //     }
    //     print("ans = {}\n", ans);
    // }

    long f_sum(long n) { // sum_{d=1} d * (n / d)
        long ret = 0;
        for (long i = 1, i2 = 0; i <= n; ) {
            long j = n / (n / i) + 1;
            long j2 = (j % MOD) * (j % MOD - 1) % MOD * inv2 % MOD;
            ret += (n / i) % MOD * ((j2 - i2) % MOD) % MOD;
            i = j;
            i2 = j2;
        }
        return ret;
    }

    void main() {
        // long ans = 1;
        // for (int d = 1; d <= n * n; ++d) {
        //     if (d % 4 != 0) {
        //         ans += 8 * d * (n * n / d);
        //     }
        // }

        long ans = ((1 + 8 * f_sum(n * n) - 32 * f_sum(n * n / 4)) % MOD + MOD) % MOD;
        print("ans = {}\n", ans);
    }
}

int main() {
    PE596::main();
    return 0;
}