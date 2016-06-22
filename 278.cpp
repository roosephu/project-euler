#include <cstdio>
#include <NTL/ZZ.h>
using namespace std;
using namespace NTL;

const int n = 5000;

int primes[n], d = 0;

// see Frobenious Number
// f(a, b, c) = g(a, b, c) + a + b + c
// f(d a, d b, c) = d f(a, b, c)

int main() {
    for (int i = 2; i <= n; ++i)
        if (ProbPrime(i)) {
            ++d;
            primes[d] = i;
        }
    long ans = 0;
    for (int i = 1; i <= d; ++i)
        for (int j = i + 1; j <= d; ++j)
            for (int k = j + 1; k <= d; ++k) {
                long p = primes[i], q = primes[j], r = primes[k];
                ans += 2 * p * q * r - p * q - q * r - r * p;
            }
    printf("ans = %ld\n", ans);
    return 0;
}
