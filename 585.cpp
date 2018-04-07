#include "lib.h"
#include <numeric>

namespace PE585 {

    const long n = 5000000, maxN = n + 20;

    int sf[maxN];

    long mul(long x, long y) {
        int g = GCD(x, y);
        return (x / g) * (y / g);
    }

    long fast_partial_sum(int n, vector<long> &Sphi) { // sum_{i=1}^n [n/i] phi(i)
        long ret = 0;
        for (long i = 1; i <= n; ) {
            long j = n / (n / i) + 1;
            ret += n / i * (Sphi[j - 1] - Sphi[i - 1]);
            i = j;
        }
        return ret;
    }

    void main() {
        for (int i = 1; i <= n; ++i) {
            sf[i] = i;
        }
        for (int i = 2; i * i <= n; ++i) {
            for (int j = 1; i * i * j <= n; ++j) {
                while (sf[i * i * j] % (i * i) == 0) {
                    sf[i * i * j] /= i * i;
                }
            }
        }
        long ans = 0;

        auto primes = sieve(n);
        auto phi = init_mul_func2<long>(
            n,
            primes,
            [](int x) -> long { return x - 1; },
            [](vector<long> &f, int n, int p) -> int { return n % p == 0 ? f[n] * p : f[n] * (p - 1); }
        );
        for (int i = 1; i <= n; ++i) {
            phi[i] /= 2;
        }
        for (int a = 1; a * a <= n; ++a) {
            for (int b = 1; b < a && a * a + b * b <= n; ++b) {
                if (GCD(a, b) == 1) {
                    phi[a * a + b * b] -= 1;
                }
            }
        }
        auto Sphi = phi;
        partial_sum(Sphi.begin(), Sphi.end(), Sphi.begin());

        // for (long a = 1; a <= n; ++a) {
        //     for (long b = 1; b < a && a + b <= n; ++b) {
        //         if (GCD(a, b) != 1 || sf[a] == sf[b]) continue;
        //         for (int u = 1; (a + b) * u <= n; ++u) {
        //             for (int v = 0; v < u && b * u > a * v && (a + b) * (u + v) <= n; ++v) {
        //                 if (sf[u] != sf[v] && sf[a * u] != sf[b * v]) {
        //                     ans += 1;
        //                 }
        //             }
        //         }
        //     }
        // }
        for (int s = 3; s <= n; ++s) {
            ans += (long)n / s * phi[s];
        }

        // for (long a = 1; a <= n; ++a) {
        //     for (long b = 1; b < a && a + b <= n; ++b) {
        //         if (GCD(a, b) != 1 || sf[a] == sf[b]) continue;
        //         ans += n / (a + b);
        //     }
        // }

        long cnt1 = 0;
        for (long i = 1; i <= n; ) {
            long j = n / (n / i) + 1;
            // for (long s2 = 1; s1 * s2 <= n; ++s2) {
            //     cnt1 += n / s1 / s2 * phi[s1] * phi[s2];
            // }
            cnt1 += (Sphi[j - 1] - Sphi[i - 1]) * fast_partial_sum(n / i, Sphi);
            i = j;
        }
        // for (long a = 1; a <= n; ++a) {
        //     for (long b = 1; b < a && a + b <= n; ++b) {
        //         if (GCD(a, b) != 1 || sf[a] == sf[b]) continue;
        //         for (int u = 1; (a + b) * u <= n; ++u) {
        //             for (int v = 1; v < u && (a + b) * (u + v) <= n; ++v) {
        //                 if (GCD(u, v) != 1 || sf[u] == sf[v]) continue;
        //                 assert((sf[a * u] == sf[b * v]) == (sf[u] * sf[v] == sf[a] * sf[b]));
        //                 cnt1 += n / (a + b) / (u + v);
        //             }
        //         }
        //     }
        // }

        long cnt3 = 463766234;
        // long cnt3 = 0;
        // for (long p = 1; (p + 1) * (p + 1) <= n; ++p) {
        //     print("{}\n", p);
        //     if (sf[p] != p) continue;
        //     for (long q = 1; (p * q + 1) * (p + q) <= n; ++q) {
        //         if (sf[q] != q) continue;
        //         if (GCD(p, q) != 1) continue;
        //         for (long r = 1; (p * q + r) * (p * r + q) <= n; ++r) {
        //             if (sf[r] != r) continue;
        //             if (GCD(p * q, r) != 1) continue;
        //             for (long s = 1; (p * q + r * s) * (p * r + q * s) <= n; ++s) {
        //                 if (sf[s] != s) continue;
        //                 if (GCD(p * q * r, s) != 1) continue;
        //                 long u = p * q, v = r * s, a = p * r, b = q * s;
        //                 if (sf[u] == sf[v] || sf[a] == sf[b]) continue;
        //                 // print("{} {} {} {}: {} {} {} {}\n", u, v, a, b, p, q, r, s);
        //                 for (int w1 = 1; (u * w1 * w1 + v) * (a + b) <= n; ++w1) {
        //                     for (int w2 = 1; (u * w1 * w1 + v * w2 * w2) * (a + b) <= n; ++w2) {
        //                         for (int w3 = 1; (u * w1 * w1 + v * w2 * w2) * (a * w3 * w3 + b) <= n; ++w3) {
        //                             for (int w4 = 1; (u * w1 * w1 + v * w2 * w2) * (a * w3 * w3 + b * w4 * w4) <= n; ++w4) {
        //                                 if (GCD(u * w1, v * w2) == 1 && GCD(a * w3, b * w4) == 1 && u * w1 * w1 > v * w2 * w2 && a * w3 * w3 > b * w4 * w4) {
        //                                     cnt3 += n / (u * w1 * w1 + v * w2 * w2) / (a * w3 * w3 + b * w4 * w4);
        //                                     // print("B: {} {} {} {}: {}\n", u * w1 * w1, v * w2 * w2, a * w3 * w3, b * w4 * w4, (u * w1 * w1 + v * w2 * w2) * (a * w3 * w3 + b * w4 * w4));
        //                                 }
        //                             }
        //                         }
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }
        print("cnt1 = {}, cnt3 = {}\n", cnt1, cnt3);
        ans += (cnt1 - cnt3) / 2;

        print("ans = {}\n", ans);
    }
}

int main() {
    PE585::main();
    return 0;
}
