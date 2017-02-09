#include "fmt/format.h"
#include <NTL/ZZ.h>
#include <algorithm>
using namespace fmt;
using namespace std;
using namespace NTL;

const int MAX_PRIMES = 10000000;
const long start = 1e16 - 2e9, LENGTH = 1e9 + 8, LMT = 1e8;
// const long start = 1, LENGTH = 100 + 8, LMT = 10;

// long mark[LENGTH], ans[LENGTH];
unsigned long mark[LENGTH / 64 + 10];

#define setbit(x, i) (x[(i) >> 6] |= 1ull << ((i) & 63))
#define getbit(x, i) (x[(i) >> 6] >> ((i) & 63) & 1)

int primes[MAX_PRIMES];

long max_prime_factor(long x) {
    long ret = 0;
    for (int i = 1; i <= primes[0]; ++i) {
        long p = primes[i];
        if (x % p == 0) {
            do {
                x /= p;
            } while (x % p == 0);
            ret = p;
        } else if (p * p > x) {
            break;
        }
    }
    ret = max(ret, x);
    return ret;
}

long calc(long n) {
    long ret = 0;
    for (int i = 0; i <= 8; ++i)
        ret += max_prime_factor(n + i);
    return ret;
}

int main() {
    PrimeSeq gen;
    // for (int i = 0; i < LENGTH; ++i)
    //     mark[i] = start + i;
    for (int p; (p = gen.next()) < LMT; ) {
        primes[++primes[0]] = p;
        long beg = (start - 1) / p;
        for (long i = (beg + 1) * p - start; i < LENGTH; i += p) {
            setbit(mark, i);
            // do {
            //     if (mark[i] % p != 0) {
            //         print("xxx {}: {}\n", i, p);
            //         return 0;
            //     }
            //     mark[i] /= p;
            // } while (mark[i] % p == 0);
            // ans[i] = p;
        }
    }
    // print("sieved\n");
    // for (int i = 0; i < LENGTH; ++i)
    //     if (mark[i] != 1)
    //         ans[i] = mark[i];

    long sum = 0, cnt = 0;
    for (int i = 0; i < LENGTH; ++i) {
        sum += getbit(mark, i);
        // print("{}: {}\n", start + i, ans[i]);
        if (i >= 9)
            sum -= getbit(mark, i - 9);
        if (i >= 8 && sum <= 5) {
            long x = start + i;
            // long y = calc(x - 8);
            cnt += 1;
            // print("#{} {}: {}\n", cnt, x, y);
            print("{},", x);
            // mx = max(mx, y);
        }
    }
    print("\n");
    // print("ans = {}\n", mx);

    return 0;
}