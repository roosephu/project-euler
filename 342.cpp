#include "fmt/format.h"
#include "fmt/ostream.h"
#include <NTL/ZZ.h>
using namespace fmt;
using namespace NTL;

const long n = 1e10, P = 1e4, diff_lmt = 5e6;

int primes[P];
long ans = 0;
int max_err = 0;

bool is_cubic(ZZ x) {
    long v = pow(conv<double>(x), 1. / 3);
    ZZ t{v - 2};
    while (t * t * t < x)
        t += 1;
    return t * t * t == x;
}

void dfs(int dep, long now, long diff, ZZ phi) {
    // check current number
    if (now != 1 && is_cubic(phi)) {
        print("find: {} phi = {}\n", now, phi);
        ans += now;
    }

    for (int i = dep; i < P; ++i) {
        long p = primes[i];
        if (diff * p > diff_lmt || now * p > n || now * p * p > n)
            break;

        ZZ y = phi * ((p - 1) * p);
        for (long x = now * p; x <= n; x *= p, y *= p * p) {
            dfs(i + 1, x, diff * p, y);
        }
    }
}

int main() {
    PrimeSeq gen;
    for (int i = 1; i < P; ++i)
        primes[i] = gen.next();
    print("{}\n", gen.next());

    dfs(1, 1, 1, ZZ(1));
    print("ans = {}\n", ans);

    return 0;
}