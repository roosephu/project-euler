#include "fmt/format.h"
#include "NTL/ZZ.h"
#include <algorithm>
using namespace fmt;
using namespace NTL;

// constraint: a^2 = b(b + c)

const long n = 1e9, L = n * 2.42;

int main() {
    long ans = 0;
    for (long u = 1; u * u <= L; ++u) {
        if (u % 1000 == 0)
            print("{}/{}\n", u * u, L);
        for (long v = 1; v < u && u * v <= n; ++v)
            if (GCD(u, v) == 1 && (u % 2 == 0 || v % 2 == 0)) {
                long p = u * u - v * v;
                long q = 2 * u * v;
                long r = u * u + v * v;
                if (p > q)
                    swap(p, q);
                // p = c, q = 2a

                if (q % 2 != 0)
                    p *= 2, q *= 2, r *= 2;
                if (p * 4 >= q * 3 || q > n * 2)
                    continue;

                long a = q / 2;
                long c = p;
                long b = (r - p) / 2;
                long cnt = n / a;
                ans += (cnt + 1) * cnt / 2 * a;
                // print("({}, {}, {}), ({}, {}, {})\n", a, b, c, p, q, r);
            }
    }
    print("ans = {}\n", ans);
    return 0;
}