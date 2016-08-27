#include "fmt/format.h"
#include <NTL/ZZ.h>
#include <cmath>
#include <algorithm>
using namespace fmt;
using namespace NTL;
using namespace std;

const long n = 1e18, phi_lb_lmt = 1e9;
const long M = 3.6e8, maxPrimes = 2e7;

int primes[maxPrimes], lb[maxPrimes];
unsigned int check[M / 8 + 100];
int cnt = 0, ans = 0;
long mx = 0;

void dfs(int pos, long v, int gcd, long phi_lb, long phi) {
    if (gcd == 1) {
        ++cnt;
        if (cnt % 10000000 == 0)
            print("cnt = {}, ans = {}\n", cnt, ans);

        if (phi % (phi_lb * phi_lb) == 0) {
            long tmp = phi, g = 0;
            for (int i = 1; i <= primes[0] && primes[i] * primes[i] <= tmp; ++i) {
                if (tmp % primes[i] == 0) {
                    int e = 0;
                    while (tmp % primes[i] == 0) {
                        ++e;
                        tmp /= primes[i];
                    }
                    g = GCD(g, e);
                }
            }
            if (g == 1) {
                ++ans;
                // print("found x = {}, phi = {}\n", v, phi);
            }
        }
    }
    int min_e = 2;
    while (gcd != 0 && GCD(min_e, gcd) != 1)
        ++min_e;
    long bound = pow(n / v, 1. / min_e) + 10;

    for (; ++pos <= primes[0]; ) {
        long p = primes[pos];
        if (p > bound)
            break;

        long n_lb = phi_lb * lb[pos] / GCD(phi_lb, lb[pos]);
        if (n_lb > phi_lb_lmt)
            continue;

        long val = v * p * p, n_phi = phi * p * (p - 1);
        for (int e = 2; ; ++e) {
            // if (val < 0) {
            //     print("v = {}, p = {}, bound = {}\n", v, p, bound);
            //     break;
            // }
            dfs(pos, val, GCD(gcd, e), n_lb, n_phi);
            if (val > n / p)
                break;
            val *= p;
            n_phi *= p;
        }
    }
}

long min_mul(int p) {
    long ret = p;

    --p;
    for (int i = 1; i <= primes[0] && primes[i] * primes[i] <= p; ++i)
        if (p % primes[i] == 0) {
            ret *= primes[i];

            while (p % primes[i] == 0)
                p /= primes[i];
        }
    if (p != 1) {
        ret *= p;
    }
    return ret;
}

int main() {

    int validPrimes = 0;
    for (int i = 2; i <= M; ++i) {
        if (i % 10000000 == 0)
            print("{}\n", i);
        if (!((check[i >> 5] >> (i & 31)) & 1)) {
            for (long j = (long)i * i; j <= M; j += i)
                check[j >> 5] |= 1u << (j & 31);
            ++primes[0];
            primes[primes[0]] = i;
            lb[primes[0]] = min_mul(i);
            if (lb[primes[0]] > 0)
                validPrimes += 1;
        }
    }
    for (int i = 1; i <= 10; ++i) {
        print("p = {}, lb = {}\n", primes[i], lb[i]);
    }
    print("#primes = {}, valid = {}\n", primes[0], validPrimes);

    dfs(0, 1, 0, 1, 1);
    print("#cnt = {}, ans = {}\n", cnt, ans);

    return 0;
}