#include <cstdio>
#include <algorithm>
using namespace std;

const long n = 1e12, MOD = 2e8;

long ans = 0;

int main() {
    ans += (n % MOD) * (n % MOD - 1) / 2 % MOD;
    for (long x = 1; x * x <= n; ++x) {
        long e = n / x / (x + 1) % MOD;
        ans += n / x / x % MOD;
        ans += e * (e + 1) / 2 % MOD;
        ans += e * (n / (x + 1) % MOD - n / x % MOD) % MOD;
    }
    ans -= n / 2 % MOD;

    for (long i = 2, j; i <= n; i = j) {
        j = n / (n / i) + 1; // interval [i, j)
        long t = (n / i) % MOD;
        ans += t * (t - 1) % MOD * ((j - i) % MOD) % MOD;
    }

    long last = 0;
    for (long x = 2; x * x <= n; ++x) {
        if (x % 1000 == 0)
            printf("%ld\n", x);
        last = x;

        long v = n / x;
        for (long i = 2, j; i <= x; i = j) {
            j = min(v / (v / i), x) + 1;
            ans -= (v / i % MOD) * ((j - i) % MOD) * 2 % MOD;
        }
    }
    for (long L = last + 1, R; L <= n; L = R) {
        R = n / (n / L) + 1;

        long v = n / L, cur = 0;
        for (long i = 2, j; i <= v; i = j) {
            j = v / (v / i) + 1;
            cur += (v / i % MOD) * ((j - i) % MOD) * 2 % MOD;
        }
        ans -= (cur % MOD) * ((R - L) % MOD) % MOD;
    }

    // for (long x = 2; x * x <= n; ++x)
    //     for (long y = 2; y <= x && x * y <= n; ++y)
    //         ans -= n / x / y * 2;
    printf("%ld\n", (ans % MOD + MOD) % MOD);
    return 0;
}
