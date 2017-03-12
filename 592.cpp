#include "fmt/format.h"
#include <algorithm>
using namespace fmt;
using namespace std;

namespace PE592 {
    const long M = 1 << 25, MOD = 1ll << 48, N = 2432902008176640000ll;
    long fac[M >> 1], tab[M >> 1];

    long mul(long A, long B) {
        long A1 = A >> 24 & 0xFFFFFF, A2 = A & 0xFFFFFF;
        long B1 = B >> 24 & 0xFFFFFF, B2 = B & 0xFFFFFF;
        return ((((A1 * B2 + A2 * B1) & 0xFFFFFF) << 24) + A2 * B2) & (MOD - 1);
    }

    long partial(long a, long b) { // (b + 1) * (b + 3) * ... * (b + 2a + 1) % MOD, given B^2 == 0 mod MOD
        assert(mul(b, b) == 0);
        long ret = fac[a];
        // long sum = mul(a + 1, a + 1);
        ret += mul(b, tab[a]);
        return ret % MOD;
    }

    long factorial(long n) { // [1 .. n]
        n = n % MOD;
        long ret = 1;
        for (long b = 0; b < n; ) { // (b, b + M]
            long a = min(M, n - b);
            ret = mul(ret, partial((a - 1) >> 1, b));
            b += a;
            if (b % 9999999 == 0)
                print("progress: {}/{}\n", b, n);
        }
        return ret;
    }

    void main() {
        fac[0] = 1, tab[0] = 1;
        for (int i = 1; i < (M >> 1); ++i) {
            int p = 2 * i + 1;
            fac[i] = mul(fac[i - 1], p);
            tab[i] = (mul(tab[i - 1], p) + fac[i - 1]) % MOD;
        }
        print("{} {}\n", fac[(M >> 1) - 1], partial((M >> 1) - 1, M));
        // print("{} {}\n", partial(2, 3), partial(2, 4));

        long ans = 1, expo = 0;
        for (long n = N; n >>= 1; )
            expo += n;
        expo %= 4;
        for (int i = 0; i < expo; ++i)
            ans *= 2;

        for (long n = N; n; n >>= 1) {
            ans = mul(ans, factorial(n));
        }
        print("ans = {:X}\n", ans);
    }
}

int main() {
    PE592::main();
    return 0;
}