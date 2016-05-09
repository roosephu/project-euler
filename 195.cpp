#include <cstdio>
#include <cmath>
using namespace std;

const long n = 1053779;

long gcd(long a, long b) {
    return a ? gcd(b % a, a) : b;
}

// http://mathworld.wolfram.com/DiophantineEquation2ndPowers.html
int main() {
    long ans = 0;
    for (long u = 2; u <= 1000000; ++u) {
        for (long v = (u / 2) + 1; v <= u; ++v) {
            if (gcd(u, v) != 1)
                continue;
            long a = 2 * u * v - u * u;
            long b = 2 * u * v - v * v;
            long c = u * u + v * v - u * v;
            if (a <= 0 || b <= 0 || c <= 0)
                continue;
            long t = gcd(a, b);
            a /= t, b /= t, c /= t;
            if (a + b - c > n * 12) {
                // printf("%ld %ld\n", u, v);
                break;
            }

            if (1. * (a + b - c) * (a + b - c) <= 12. * n * n) {
                // printf("%ld %ld %ld, u = %ld, v = %ld, t = %ld\n", a, b, c, u, v, t);
                // ans += sqrt(12. * n * n * t * t / (1. * (2 * v - u) * (2 * v - u) * (2 * u - v) * (2 * u - v)));
                ans += sqrt(12. * n * n / (1. * (a + b - c) * (a + b - c)));
            }
            // if (a == b)
            //     continue;
            // a = b - a;
            // if (3. * a * a * b * b <= 4. * n * n * (a + b + c) * (a + b + c)) {
            //     printf("%ld %ld %ld\n", a, b, c);
            //     ans += sqrt(4. * n * n * (a + b + c) * (a + b + c) / (3. * a * a * b * b));
            // }
        }
    }
    printf("%ld\n", ans);
    return 0;
}
