#include <cstdio>
#include <NTL/ZZ.h>
#include <vector>
using namespace std;
using namespace NTL;

const long n = 1e11, m = 2017;
const long LMT = 1e5;

vector<long> dvs, primes;
bool is_p[LMT + 10];

long sum_mul(long d) {
    long x = n / d;
    return x * (x + 1) / 2 * d;
}

int main() {
    printf("%ld\n", NTL_SP_BOUND);
    for (int i = 2; i <= LMT; ++i)
        if (!is_p[i]) {
            primes.push_back(i);
            for (int j = i; j <= LMT; j += i)
                is_p[i] = true;
        }
    int cnt = 0;

    long ans = 0;
    for (int i = 2; i < m; ++i) {
        int e = 1;
        for (long t = i; t != 1; t = t * i % m)
            ++e;

        if (e <= 4 && e >= 2) {
            long last = 0;
            for (long p = i; ; p += m) {
                long pow = 1;
                for (int x = 1; x < e; ++x) {
                    pow *= p;
                    if (pow > n)
                        break;
                }
                if (pow > n)
                    break;

                // bool is_prime = true;
                // for (auto &x : primes) {
                //     if (x * x > p) break;
                //     if (p % x == 0) {
                //         is_prime = false;
                //         break;
                //     }
                // }
                // if (!is_prime)
                //     continue;
                if (ProbPrime(p) == 0)
                    continue;

                if (p > last) {
                    last += 100000000;
                    printf("p = %ld, cnt = %d, prime pow = %ld\n", p, e, pow);
                }

                ++cnt;

                ans += sum_mul(pow);
                if (pow <= n / p)
                    ans -= sum_mul(pow * p);

                if (1e4 * pow <= n) {
                    for (auto v : dvs)
                        if (v <= n / pow)
                            ans -= sum_mul(v * pow);
                    dvs.push_back(pow);
                }
            }
        }
    }
    printf("count: %d, ans = %ld\n", cnt, ans);
    printf("|dvs| = %d\n", (int) dvs.size());
    return 0;
}
