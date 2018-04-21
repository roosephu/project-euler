#include "lib.h"

namespace PE625 {
    const long n = 1e11;
    const long MOD = 998244353;

    map<long, long> F_;

    long C2(long n) {
        n = n % MOD;
        return n * (n + 1) % MOD * ((1 + MOD) / 2) % MOD;
    }

    long F(long n) {
        if (n == 1) {
            return 1;
        }
        if (!F_.count(n)) {
            long sum = C2(n);
            for (long i = 2; i <= n;) {
                long j = n / (n / i) + 1;
                sum -= ((j - i) % MOD) * F(n / i);
                i = j;
            }
            F_[n] = (MOD + sum % MOD) % MOD;
        }
        return F_[n];
    }

    void main() {
        long ans = 0;
        long cnt = 0;
        for (long i = 1; i <= n; ) {
            long j = n / (n / i) + 1;
            long p = n / i;
            ans += C2(p) * (F(j - 1) - F(i - 1)) % MOD;
            i = j;

            cnt += 1;
            if (cnt % 100 == 0)
                print("i = {}, size F = {}\n", i, F_.size());
        }
        print("ans = {}\n", ans % MOD);
    }
}

int main() {
    PE625::main();
    return 0;
}
