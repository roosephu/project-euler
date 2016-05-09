#include <cstdio>
using namespace std;

const int n = 50000, r = n, N = n + 100;
const long MOD = 1000000123;

long fpm(long b, long e, long m) { long t = 1; for (; e; e >>= 1, b = b * b % m) e & 1 ? t = t * b % m : 0; return t; }

int b = 0;
long w[N], u[N];
long f[N];
long fac[N], caf[N];

long solve() {
    for (int i = 0; i <= b; ++i)
        f[i] = 0;
    f[0] = fac[n];

    for (int i = 0; i < b; ++i) {
        if (i % 1000 == 1)
            printf("%d\n", i);
        int len = 0;
        for (int j = i + 1; j <= b; ++j) {
            len += w[j];
            if ((j - i) % 2 == 1)
                (f[j] += f[i] * caf[len]) %= MOD;
            else
                (f[j] += MOD - f[i] * caf[len] % MOD) %= MOD;
        }
        // printf("%d: %ld\n", i, f[i]);
    }
    return f[b] % MOD;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * fpm(i, r, MOD) % MOD;
    caf[n] = fpm(fac[n], MOD - 2, MOD);
    for (int i = n; i >= 1; --i)
        caf[i - 1] = caf[i] * fpm(i, r, MOD) % MOD;

    // w[1] = 2, w[2] = 2, w[3] = 2, b = 3;
    // w[1] = w[2] = w[3] = w[4] = 7, w[5] = 2, b = 5
    // printf("%ld\n", solve());

    long ans = 0;
    for (int i = 1; i <= n; ++i) {
        b = 0;
        for (int x = n; x; ) {
            if (x >= i)
                w[++b] = i;
            else
                w[++b] = x;
            x -= w[b];
        }
        printf("n = %d, i = %d, b = %d: ", n, i, b);
        // for (int x = 1; x <= b; ++x) {
        //     printf("%ld, ", w[x]);
        // }
        printf("\n");

        ans += solve();
    }
    printf("ans = %ld\n", ans % MOD);

    return 0;
}
