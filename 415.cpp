#include "fmt/format.h"
#include "fmt/ostream.h"
#include <NTL/ZZ.h>
#include <map>
#include "mertens.h"
using namespace fmt;
using namespace std;
using namespace NTL;

const long n = 4, N = n + 10, maxT = 10000;
const long nn = n + 1;
const long MOD = 2e8;

int primes[N], mu[N];
long g[maxT + 10];

long cb2(long n) {
    n = n % MOD;
    if (n % 2 == 0)
        return (n / 2) * (n + 1) % MOD;
    return ((n + 1) / 2) * n % MOD;
}

long func(long k) {
    long r = nn / k % MOD;
    long s = (nn % MOD * r - k % MOD * cb2(r)) % MOD;
    return s * s % MOD;
}

long G(long n) {
    if (n <= maxT) {
        return g[n];
    }
    long ret = 0;
    for (int i = 1, pi = PowerMod(2, i, MOD); i <= n; ) {
        int j = n / (n / i) + 1, pj = PowerMod(2, j, MOD);
        ret += func(n / i) * (pj - pi) % MOD;
        i = j, pi = pj;
    }
    return (ret % MOD + MOD) % MOD;
}

int main() {
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!primes[i]) primes[++primes[0]] = i, mu[i] = -1;
        for (int j = 1, k = n / i, t; primes[j] <= k; ++j) {
            primes[t = i * primes[j]] = 1;
            if (i % primes[j] != 0) mu[t] = -mu[i];
            else {mu[t] = 0; break; }
        }
    }

    for (int m = 1; m <= 100; ++m) {
        int s = 0;
        for (int i = 1; i <= m; ++i)
            s += i * mu[i];
        print("{} {}\n", m, s);
        // M += mu[m];
    }

    long n2 = (nn % MOD) * (nn % MOD) % MOD;
    long ans = (PowerMod(2, n2 % MOD, MOD) - 1 + cb2(n2) - 2 * nn % MOD * (PowerMod(2, nn, MOD) - 1) % MOD) % MOD;

    long p0 = 0;
    for (int d = 1; d <= nn; ++d)
        for (int t = 1; t * d <= nn; ++t)
            p0 += func(d * t) * PowerMod(2, d, MOD) * mu[t];

    for (int d = 1; d <= maxT; ++d) {
        for (int t = 1; t * d <= maxT; ++t) {
            g[t * d] += PowerMod(2, d, MOD) * func(d * t) % MOD;
        }
        g[d] = ((g[d] + g[d - 1]) % MOD + MOD) % MOD;
    }

    long p1 = 0;
    for (int i = 1; i <= nn; ++i) {
        p1 += mu[i] * g[nn / i];
    }
    // for (int i = 1; i <= nn; ) {
    //     int j = nn / (nn / i) + 1;
    //     p1 += (Mertens(j - 1) - Mertens(i - 1)) % MOD * G(nn / i) % MOD;
    //     i = j;
    // }
    p1 = (p1 % MOD + MOD) % MOD;

    ans = (ans - p0 % MOD + MOD) % MOD;
    print("ans = {}, p0 = {}, p1 = {}\n", ans, p0 % MOD, p1);
    return 0;
}
