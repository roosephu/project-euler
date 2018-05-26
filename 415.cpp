#include "fmt/format.h"
#include "fmt/ostream.h"
#include <NTL/ZZ.h>
#include <map>
#include "mertens.h"
using namespace fmt;
using namespace std;
using namespace NTL;

const long n = 1e11, N = n + 10, maxT = 10000, maxR = 4e5;
const long nn = n + 1;
const long MOD = 2e8;

// int primes[N], mu[N];
long g[maxT + 10];
const long inv3 = (MOD + 1) / 3;
long R, tab, basis[maxR * 2];

long cb2(long n) {
    n = n % MOD;
    if (n % 2 == 0)
        return (n / 2) * (n + 1) % MOD;
    return ((n + 1) / 2) * n % MOD;
}

long fpm(long b, long e, long m) {
    long t = 1;
    for (; e; e >>= 1, b = b * b % m) {
        e & 1 ? t = t * b % m : 0;
    }
    return t;
}

long func(long k) {
    long r = nn / k % MOD;
    long s = (nn % MOD * r - k % MOD * cb2(r)) % MOD;
    return s * s % MOD;
}

long powerSum(long n, long k) {
    n = n % MOD;
    if (k == 0) return n % MOD;
    if (k == 1) return cb2(n) % MOD;
    if (k == 2) return cb2(n) * (n % MOD * 2 + 1) % MOD * inv3 % MOD;
    return 0;
}

long potential(long n, long k) {
    if (k < 0 || n <= k) return 0;
    long ret = 0;
    if (k == 0) ret = 1;
    if (k == 1) ret = n - 1;
    if (k == 2) ret = cb2(n - 2);
    ret = ret % MOD * fpm(2, n, MOD) % MOD - 2 * potential(n - 1, k - 1) % MOD;
    if (k <= 1) ret -= 2;
    ret = (ret % MOD + MOD) % MOD;
    return ret;
}

// map<long, long> F[2][2];
int F[2][2][maxR * 2];

long dfs(long n, int a, int b, bool compute=false) {
    int A = a, B = b;

    int idx = n <= R ? tab - n : nn / n - 1;
    // if (!F[a][b].count(n)) {
    if (compute) {
        // if (F[a][b].size() % 100 == 0)
        //     print("{}\n", F[a][b].size());
        for (int a = 0; a < 2; ++a) {
            for (int b = 0; b < 2; ++b) {
                long S = powerSum(n, a) * powerSum(n, b) % MOD;
                long last_coef = powerSum(1, a + b);
                for (long i = 2; i <= n; ) {
                    long j = n / (n / i) + 1;
                    long coef = powerSum(j - 1, a + b);
                    S -= (coef - last_coef) * dfs(n / i, a, b) % MOD;

                    last_coef = coef;
                    i = j;
                }
                F[a][b][idx] = (S % MOD + MOD) % MOD;
            }
        }

    }
    return F[A][B][idx];
}

int main() {
    // mu[1] = 1;
    // for (int i = 2; i <= n; ++i) {
    //     if (!primes[i]) primes[++primes[0]] = i, mu[i] = -1;
    //     for (int j = 1, k = n / i, t; primes[j] <= k; ++j) {
    //         primes[t = i * primes[j]] = 1;
    //         if (i % primes[j] != 0) mu[t] = -mu[i];
    //         else {mu[t] = 0; break; }
    //     }
    // }

    // for (int m = 1; m <= 100; ++m) {
    //     int s = 0;
    //     for (int i = 1; i <= m; ++i)
    //         s += i * mu[i];
    //     // print("{} {}\n", m, s);
    //     // M += mu[m];
    // }

    long n2 = (nn % MOD) * (nn % MOD) % MOD;
    long ans = (fpm(fpm(2, nn, MOD), nn, MOD) - 1 + cb2(n2) - 2 * nn % MOD * (fpm(2, nn, MOD) - 1) % MOD) % MOD;

    // long p0 = 0;
    // for (int d = 1; d <= nn; ++d)
    //     for (int t = 1; t * d <= nn; ++t)
    //         p0 += func(d * t) * PowerMod(2, d, MOD) * mu[t];

    // long p1 = 0;
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n; ++j) {
    //         p1 += (nn - i) * (nn - j) * (1ll << GCD(i, j));
    //     }
    // }

    // long p1 = 0;
    // for (long g = 1; g <= nn; ++g) {
    //     long S00 = dfs(nn / g, 0, 0);
    //     long S01 = dfs(nn / g, 0, 1);
    //     long S10 = dfs(nn / g, 1, 0);
    //     long S11 = dfs(nn / g, 1, 1);
    //     print("{} {} {} {} {}\n", g, S00, S01, S10, S11);

    //     p1 += PowerMod(2, g, MOD) * (S00 * nn % MOD * nn % MOD - (S01 + S10) * nn % MOD * g % MOD + S11 * g % MOD * g % MOD);
    // }
    // p1 = (p1 % MOD + MOD) % MOD;

    long p2 = 0;

    R = SqrRoot(nn);

    for (int i = 1; nn / i > R; ++i) {
        basis[++tab] = nn / i;
    }
    for (int i = R; i; --i) {
        basis[++tab] = i;
    }
    for (int i = tab; i; --i) {
        if (i % 1000 == 0) {
            print("{}\n", i);
        }
        dfs(basis[i], 0, 0, true);
    }

    long pi0 = potential(1, 0), pi1 = potential(1, 1), pi2 = potential(1, 2);
    for (long i = 1; i <= nn; ) {
        long j = nn / (nn / i) + 1;

        long S00 = dfs(nn / i, 0, 0);
        long S01 = dfs(nn / i, 0, 1);
        long S10 = dfs(nn / i, 1, 0);
        long S11 = dfs(nn / i, 1, 1);

        long pj0 = potential(j, 0);
        long pj1 = potential(j, 1);
        long pj2 = potential(j, 2);

        // print("{} {} ({}, {}, {}, {}), ({}, {}, {})\n", i, j, S00, S01, S10, S11, pj0 - pi0, pj1 - pi1, pj2 - pi2);

        p2 += S00 * (nn % MOD) % MOD * (nn % MOD) % MOD * (pj0 - pi0) % MOD;
        p2 -= (S01 + S10) * (nn % MOD) % MOD * (pj1 - pi1) % MOD;
        p2 += S11 * ((pj2 - pi2) * 2 + pj1 - pi1) % MOD;

        i = j;
        pi0 = pj0;
        pi1 = pj1;
        pi2 = pj2;
    }
    p2 = (p2 % MOD + MOD) % MOD;

    ans = (ans + MOD - p2 % MOD + MOD) % MOD;
    // print("ans = {}, p0 = {}, p1 = {}, p2 = {}\n", ans, p0 % MOD, p1, p2);
    print("ans = {}\n", ans);
    return 0;
}
