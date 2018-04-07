#include "lib.h"

namespace PE478 {
    const int n = 1e7;
    const long MOD = 214358881, PHI_MOD = MOD / 11 * 10 * 2;

    // map<tuple<int, int>, int> f;
    vector<int> primes, mu, phi, mertens;

    // tuple<int, int> find(int a, int b, int c) {
    //     if (abs(a) > abs(b)) swap(a, b);
    //     if (abs(b) > abs(c)) swap(b, c);
    //     if (abs(a) > abs(b)) swap(a, b);
    //     if (a == 0 && b < c) swap(b, c);
    //     return {a, b};
    // }

    // int F(int s, int n) {
    //     int ret = 0;
    //     for (int t = 1; t * s <= n; ++t) {
    //         for (int k = 0; k <= n - t * s; ++k) {
    //             ret += GCD(t, k) == 1;
    //         }
    //     }
    //     return ret;
    // }

    long f[n + 10], g[n + 10];

    long F(int s, int n) {
        long ret = 0;
        for (long i = 1; i * s <= n; ) {
            long j = n / (n / i) + 1;
            long t = n / i, d = t / s;
            long g = 0;
            g = (2 * t % PHI_MOD + 2 - s * (1 + d)) % PHI_MOD * d % PHI_MOD / 2;
                // g = (t % PHI_MOD + 1 - s * (1 + d) / 2) % PHI_MOD * d % PHI_MOD;
            ret += g * (mertens[j - 1] - mertens[i - 1]) % PHI_MOD;
            i = j;
        }
        return (ret % PHI_MOD + PHI_MOD) % PHI_MOD;
    }

    void main() {
        // long ans = PowerMod(2, (n + 1) * (n + 1) * (n + 1) - 1, MOD);
        print("before sieve\n");
        primes = sieve(n + 1);
        print("sieved\n");
        mu = init_mul_func2<int>(n + 1, primes,
            // [](int p, int e) -> int { return e == 1 ? -1 : 0; }
            [](int x) -> int { return -1; },
            [](vector<int> &f, int n, int p) -> int { return n % p == 0 ? 0 : -f[n]; }
        );
        print("mu\n");
        phi = init_mul_func2<int>(n + 1, primes,
            // [](int p, int e) -> int {
            //     long t = p - 1;
            //     for (; e > 1; --e) t *= p;
            //     return t;
            // }
            [](int x) -> int { return x - 1; },
            [](vector<int> &f, int n, int p) -> int { return n % p == 0 ? f[n] * p : f[n] * (p - 1); }
        );
        print("phi\n");
        mertens.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            mertens[i] = mertens[i - 1] + mu[i];
        }

        long total = 0;
        for (int i = 1; i <= n; ++i) {
            long x = n / i + 1;
            total += mu[i] * (x * x % PHI_MOD * x % PHI_MOD - 1) % PHI_MOD;
        }
        total = (total % PHI_MOD + PHI_MOD) % PHI_MOD;

        // for (int s = 1; s <= n; ++s) {
        //     long sum = 0;
        //     for (int d = 1; d <= n; ++d) {
        //         sum += F(s, n / d);
        //     }
        //     print("s = {}, sum = {}, est = {}\n", F(s, n), sum, FF(s, n));
        // }

        // long total = 0;
        // for (int i = 0; i <= n; ++i) {
        //     for (int j = 0; j <= n; ++j) {
        //         for (int k = 0; k <= n; ++k) {
        //             if (!i && !j && !k) continue;
        //             if (i == 1 && j == 1 && k == 1) continue;
        //             if (GCD(i, GCD(j, k)) != 1) continue;

        //             long a = i - j, b = j - k, c = k - i;
        //             tie(a, b) = find(a, b, c);
        //             long g = abs(GCD(a, b));
        //             if (a < 0 || (a == 0 && b < 0)) g = -g;

        //             f[{a / g, b / g}] += 1;
        //             total += 1;
        //         }
        //     }
        // }
        long ans = PowerMod(2, total, MOD); // (1, 1, 1)
        print("total = {}\n", total);
        // map<tuple<int, int>, vector<tuple<int, int, int, int>>> g;
        // for (auto [k, v] : f) {
        //     auto [a, b] = k;
        //     // g[find(a, b, 0 - a - b)].push_back({a, b, 0 - a - b, v});
        //     long M = (b == 1) ? 6 : 12;
        //     print("({}, {}) -> {}, {}, {}\n", a, b, v / M, M, F(a + b, n));
        //     // if (f[za, b}] != f[{b, a}] || f[{a, b}] != f[{b, -a - b}] || f[{b, -a - b}] != f[{a, b}]) print("!!!");
        //     ans -= M * (PowerMod(2, total / 2, MOD) - PowerMod(2, total / 2 - v / M, MOD)) % MOD;
        //     ans = (MOD + ans % MOD) % MOD;
        // }
        // for (auto [k, v] : g) {
        //     auto [a1, b1] = k;
        //     print("({}, {}) => ", a1, b1);
        //     for (auto [a, b, c, vv] : v) {
        //         print("({}, {}, {}, {}) ", a, b, c, vv);
        //     }
        //     print("\n");
        // }
        for (int b = 1; b <= n; ++b) {
            long M = 6 * phi[b];
            long f = F(b, n);
            // print("{} {}\n", b, f);
            ans -= M * (PowerMod(2, (total - 1) / 2, MOD) - PowerMod(2, (total - 1) / 2 - f + PHI_MOD, MOD)) % MOD;
            ans = (MOD + ans % MOD) % MOD;
        }
        ans -= 1; // empty set
        print("ans = {}\n", ans);
    }
}

int main() {
    PE478::main();
    return 0;
}
