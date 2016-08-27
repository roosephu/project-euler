#include "fmt/format.h"
#include <NTL/ZZ.h>
#include <algorithm>
using namespace std;
using namespace NTL;
using namespace fmt;

const long n = 1e10, N = 2e7;

int primes[N];

bool is_practical(long n) {
    long s = 1;
    // print("{} ", n);
    for (int i = 1; s < n; ++i) {
        long p = primes[i], q = 1;
        if (p * p > n || p > s + 1)
            break;
        while (n % p == 0) {
            n /= p;
            q = q * p + 1;
        }
        if (q != 1) {
            // print("{},", p);
            s *= q;
        }
    }
    // print("\n");
    return s >= n;
}

bool is_prime(long n) {
    return ProbPrime(n);
}

int main() {
    PrimeSeq gen;
    for (int i = 1; i < N; ++i)
        primes[i] = gen.next();
    // print("{}\n", gen.next());
    // for (int i = 1; i <= 200; ++i)
    //     if (is_practical(i))
    //         print("{}\n", i)
    //         ;

    long cnt = 0, ans = 0;
    for (long i = 10; i <= n; i += 10) {
        if (i % 10000000 == 0)
            print("{}\n", i);
        bool prime_criterion =
            is_prime(i - 9) &&
            is_prime(i - 3) &&
            is_prime(i + 3) &&
            is_prime(i + 9);
        bool practical_criterion =
            prime_criterion &&
            is_practical(i - 8) &&
            is_practical(i - 4) &&
            is_practical(i) &&
            is_practical(i + 4) &&
            is_practical(i + 8);
        bool consecutive_criterion =
            practical_criterion &&
            !is_prime(i - 7) &&
            !is_prime(i - 1) &&
            !is_prime(i + 1) &&
            !is_prime(i + 7);

        if (consecutive_criterion) {
            print("found: {}\n", i);
            cnt += 1;
            ans += i;

            if (cnt == 4)
                break;
        }
    }

    print("ans = {}\n", ans);
    return 0;
}
