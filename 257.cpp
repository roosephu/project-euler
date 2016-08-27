#include "fmt/format.h"
#include <cmath>
#include <NTL/ZZ.h>
using namespace fmt;
using namespace std;
using namespace NTL;

const long n = 1e8;

int main() {
    long ans = n / 3;
    long ans2 = 0;
    // for (int c = 1; c <= n; ++c)
    //     for (int b = 1; b <= c; ++b)
    //         for (int a = c - b + 1; a <= b; ++a)
    //             if ((a + b) * (a + c) % (b * c) == 0 && a + b + c <= n) {
    //                 ++ans2;
    //                 // print("bf {} {} {}\n", a, b, c);
    //             }
    // print("{}\n", ans2);

    for (int k = 2; k <= 3; ++k) {
        print("{}\n", k);
        long upper = sqrt(sqrt(k) * k / (sqrt(k) - 1) / (sqrt(k) - 1) * n) + 1000;
        for (long b = 1; b <= upper; ++b) {
            // print("{}\n", b);
            for (long a = (sqrt(k) - 1) * b; 2 * a <= (k - 1) * b; ++a) {
                if (GCD(a, b) != 1) continue;
                long A = a * ((k - 1) * b - a);
                long B = b * ((k - 1) * b - a);
                long C = a * (a + b);
                long g = GCD(((k - 1) * b - a), C);
                if (g != 1) {
                    A /= g;
                    B /= g;
                    C /= g;
                }
                if (A + B > C && A <= B && B <= C && A + B + C <= n) {
                    // print("{}, {}, {} = {}, a = {}, b = {}\n", A, B, C, (A + B) * (A + C) % (B * C), a, b);
                    long cnt = n / (A + B + C);
                    ans += cnt; // * (cnt + 1) / 2 * (A + B + C);
                }
            }
        }
    }
    print("ans = {}\n", ans);
    return 0;
}