#include "fmt/format.h"
#include "fmt/ostream.h"
#include <NTL/ZZ.h>
using namespace fmt;
using namespace NTL;

const long n = 1e2;
const ZZ Z_n(n);

ZZ F2(ZZ n) {
    return (n * n - n + 12) * (n + 1) * (n + 2) / 24;
}

ZZ F1(ZZ n) {
    return (n * n - n + 6) * (n + 1) / 6;
}

ZZ F3(ZZ n) {
    return (n * n - n + 20) * (n + 1) * (n + 2) * (n + 3) / 120;
}

ZZ Min(ZZ a, ZZ b) {
    return a < b ? a : b;
}

int main() {
    ZZ ans(0);
    // for (long t = LMT + 1; t <= n + 2; ++t) {
    //     long R = SqrRoot(t * t + 4 * n);
    //     long cnt = 0;
    //     while ((t - R) % 2 != 0 || R > n)
    //         --R;
    //     if (t * t <= 4 * n) {
    //         cnt = R + 1;
    //     } else {
    //         long L = SqrRoot(t * t - 4 * n - 1) + 1;
    //         while ((t - L) % 2 != 0 || L < -n)
    //             ++L;
    //         cnt = R - L + 2;
    //     }
    //     ans += cnt * (t * (t * t + 5) / 6 + 1);
    // }

    // k = 0, +1, -1
    ans += F2(Z_n) + F2(Z_n + 1) + F2(Z_n - 2) + F1(Z_n) + F1(Z_n + 1);

    for (ZZ x(2); x < n; ) {
        ZZ next = Min(Z_n / (Z_n / x) + 1, Z_n);
        // interval for t: [max(k - ceil(n / |k|), 0), k + floor(n / |k|)]
        ZZ c = Z_n / x;
        ans += F3(next - 1 + c) - F3(x - 1 + c);
        if (x > c)
            ans -= F3(next - 1 - c - 1) - F3(x - 1 - c - 1);
        else
            ans += F3(c - x) - F3(c - next);
        // for (long k = x; k < next; ++k) {
            // ans += prefix(k + n / k);
            // if (k * k > n)
            //     ans -= prefix(k - ((n - 1) / k + 1) - 1);
            // if (k * k < n)
            //     ans += prefix(-k + (n / k));
            // ans += F2(c + k);
        //     if (k > c)
        //         ans -= F2(k - c - 1);
        //     else
        //         ans += F2(c - k);
        // }
        // print("x = {}, c = {}, next - 1 = {}\n", x, c, next - 1);

        x = next;
    }

    ans %= ZZ((long) 1e8);
    print("ans = {}\n", ans);
    return 0;
}
