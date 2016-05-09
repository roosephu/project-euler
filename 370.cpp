#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const long n = 2.5e10, m = 1e7 + 10, M = m + 10;

long mu[M], primes[M];

long gcd(long a, long b) {
    return a ? gcd(b % a, a) : b;
}

long solve(long a, long n) {
    long b = (sqrt(4 * n - 3 * a * a) - a) / 2 - 1;
    while (a * a + a * b + b * b < n)
        ++b;
    return b;
}

long compute(long n) {
    // for (long i = 1, j = 1, t = 1; i <= n; ++t) {
    //     j = n / (n / i) + 1;
    //     points[t] = i;
    //     i = j;
    // }
    long ret = 0;
    for (long a = 1; 3 * a * a <= n; ++a) {
        long b = min(long(a * 1.618), solve(a, n + 1)) - 1;
        for (; a * a + a * b + b * b <= n && a * a + a * b > b * b;)
            ++b;
        if (b < a)
            continue;

        // b in [a, b]

        long curB = a;
        long delta = 0;
        long iter = 0;
        // printf("a = %ld, start point = %ld\n", a, n / (n / (3 * a * a)));
        for (long point = n / (n / (3 * a * a)); ; ) {
            ++iter;
            long nextPoint = n / (n / point) + 1;
            long nextB = solve(a, nextPoint);
            // printf("cur point = %ld, next point = %ld, next b = %ld, max b = %ld\n", point, nextPoint, nextB, b);
            if (nextB >= b) {
                delta += n / point * (b - curB);
                break;
            } else if (nextB > curB) {
                delta += n / point * (nextB - curB);
                curB = nextB;
            }
            point = nextPoint;
        }
        ret += delta;
        // printf("iter = %ld\n", iter);

    }
    // long ret2 = 0;
    // for (long a = 1; a * a * 3 <= n; ++a)
    //     for (long b = a; a * a + a * b > b * b && a * a + b * b + a * b <= n; ++b)
    //         ret2 += n / (a * a + b * b + a * b);
    // printf("ret = %ld, ret2 = %ld, n = %ld\n", ret, ret2, n);
    return ret;
}

int main() {
    // printf("%ld\n", compute(n));
    for (int i = 2; i <= m; ++i) {
        if (!primes[i]) primes[++primes[0]] = i, mu[i] = -1;
        for (int j = 1, k = m / i; primes[j] <= k; ++j) {
            int t = i * primes[j]; primes[t] = 1;
            if (i % primes[j] != 0) mu[t] = -mu[i];
            else {mu[t] = 0; break; }
        }
    }
    mu[1] = 1;

    long ans = 0;
    for (long t = 1; t * t <= n; ++t) {
        ans += mu[t] * compute(n / t / t);
    }
    printf("ans = %ld\n", ans);
    return 0;
}
