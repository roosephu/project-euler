#include "fmt/format.h"
#include <NTL/ZZ.h>
using namespace fmt;
using namespace NTL;

const int n = 1e8;

// cos(theta) must be rational.
// 60, ?, ? => 4 a^2 = (2 b - c)^2 + 3 c^2
// 90, ?, ? => a * a = b * b + c * c
// 120, ?, ? => 4 a^2 = (2 b + c)^2 + 3 c^2

// 4 a^2 = b^2 + 3 c^2
// (2a + b)(2a - b) = 3 c^2
// 1. 2a + b = 3 t p^2, 2a - b = t q^2, c = t p q
// 2. 2a - b = 3 t p^2, 2a + b = t q^2, c = t p q

int main() {
    int cnt = 0, mx = 0;
    long ans = 0;

    for (int p = 1; 3 * p * p <= 4 * n; p += 2) {
        for (int q = 1; 3 * p * p + q * q + 4 * p * q <= 4 * n; q += 2) {
            if (GCD(p, q) == 1) {
                int A = 3 * p * p, B = q * q, C = p * q;
                if (A < B)
                    swap(A, B);
                if ((A + B) % 4 != 0 || ((A - B) / 2 + C) % 2 != 0)
                    continue;

                int a = (A + B) / 4, c = C;
                cnt += 1;
                mx = p;
                ans += n / (a + ((A - B) / 2 + c) / 2 + c);
                if ((A - B) / 2 != c)
                    ans += n / (a + abs((A - B) / 2 - c) / 2 + c);
                // print("{} {} {}\n", a,    ((A - B) / 2 + c) / 2, c);
                // print("{} {} {}\n", a, abs((A - B) / 2 - c) / 2, c);
            }
        }
    }
    for (int p = 1; p * p * 2 <= n; ++p) {
        for (int q = 1; q < p && p * (p + q) * 2 <= n; ++q) {
            if (GCD(p, q) == 1 && (p + q) % 2 == 1) {
                int a = p * p - q * q;
                int b = 2 * p * q;
                int c = p * p + q * q;

                ans += n / (a + b + c);
            }
        }
    }
    print("cnt = {}, mx = {}\n", cnt, mx);
    print("ans = {}\n", ans);
    return 0;
}