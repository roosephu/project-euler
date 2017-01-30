#include "fmt/format.h"
#include "fmt/ostream.h"
#include <NTL/lzz_p.h>
#include <map>
using namespace fmt;
using namespace std;
using namespace NTL;

const long n = 1e11, N = n + 10;

// int primes[N], mu[N];
map<long, zz_p> G;
zz_p two;

zz_p cb2(zz_p n) {
    long t = rep(n);
    if (t % 2 == 0)
        return zz_p(t / 2) * (t + 1);
    return zz_p((t + 1) / 2) * t;
}

zz_p func(long k) {
    zz_p r{(n + 1) / k};
    zz_p s = (n + 1) * r - k * cb2(r);
    return s * s;
}

zz_p get_G(long n) {
    if (n == 1)
        return two;
    if (!G.count(n)) {
        zz_p ret = power(two, n + 1) - 2;
        for (long i = 2, j; i <= n; ) {
            j = n / (n / i) + 1;
            ret -= (j - i) * get_G(n / i);
            i = j;
        }
        G[n] = ret;
    }
    return G[n];
}

int main() {
    zz_p::init(200000000);
    two = zz_p(2);

    // mu[1] = 1;
    // for (int i = 2; i <= n; ++i) {
    //     if (!primes[i]) primes[++primes[0]] = i, mu[i] = -1;
    //     for (int j = 1, k = n / i, t; primes[j] <= k; ++j) {
    //         primes[t = i * primes[j]] = 1;
    //         if (i % primes[j] != 0) mu[t] = -mu[i];
    //         else {mu[t] = 0; break; }
    //     }
    // }

    zz_p n2 = (n + zz_p(1)) * (n + 1);
    zz_p ans = power(power(two, n + 1), n + 1) - 1 + cb2(n2) - 2 * (n + 1) * (power(two, n + 1) - 1);

    int cnt = 0;
    zz_p p0{0};
    for (long d = 1, m = n + 1; d <= n; ++d) {
        long D = min(m / (m / d) + 1, n);
        p0 += 2 * m * partial_sum(2^d, d, D - 1) * (partial_sum(mu(k) * (m / k / d), 1, n / d));
        p0 -=
    }

    // zz_p p0{0};
    // for (int d = 1; d <= n; ++d)
    //     for (int t = 1; t * d <= n; ++t)
    //         p0 += func(d * t) * power(two, d) * mu[t];

    ans -= p0;
    print("ans = {}, p0 = {}\n", ans, p0);
    return 0;
}