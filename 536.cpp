#include "fmt/format.h"
#include <vector>
#include <NTL/ZZ.h>
using namespace std;
using namespace fmt;
using namespace NTL;

const long n = 1e12;
const int numPrimes = 8e4;

int primes[numPrimes + 10];
long ans = 0;
long dvs[100000], pd[100], top, total;

long lcm(long a, long b) {
    long g = GCD(a, b);
    return a / g * b;
}

int cnt = 0, verified = 0, factored = 0, checked = 0;

void verify(long m, long l) {
    // print("verify: {} {}\n", m, l);
    ++verified;
    if (m <= n && (m + 3) % l == 0) {
        cnt += 1;
        ans += m;
        // print("found (#{}) {}, verified = {}\n", cnt, m, verified);
    }
}

void factor(long m, int top) {
    if (top == 0) {
        ++total;
        dvs[total] = m;
    } else {
        factor(m, top - 1);
        for (; m % pd[top] == 0; ) {
            m /= pd[top];
            factor(m, top - 1);
        }
    }
}

void divisors(long m) {
    long old = m;
    top = 0;
    for (int i = 1; ; ++i) {
        long p = primes[i];
        if (p * p > m)
            break;
        if (m % p == 0) {
            ++top;
            while (m % p == 0)
                m /= p;
            pd[top] = p;
        }
    }
    if (m != 1)
        pd[++top] = m;

    total = 0;
    factor(old, top);
}

void dfs(int dep, long l, long m) {
    if (primes[dep] * m > n)
        return;
    checked += 1;
    if (checked % 10000 == 0)
        print("checked = {}, cnt = {}, m = {}, verified = {}\n", checked, cnt, m, verified);
    // print("m = {}, l = {}, verified = {}\n", m, l, verified);

    // if (m > 100000) {
    //     long lim = mul(l - 3, fpm(m, phi(l) - 1, m), l);
    //     ++check;
    //     if (lim > n / m) {
    //         printf("hit! check = %d\n", check);
    //     }
    // }
    // if ((m + 3) % l == 0) {
    //     // cnt += 1;
    //     print("{}: {}\n", cnt, m);
    //     // analyse(m);
    //     // ans += m;
    // }
    if (true) {
        divisors(m + 3);
        for (int i = 1; i <= total; ++i) {
            long d = dvs[i] + 1;
            if (d >= primes[dep] && ProbPrime(d))
                verify(m * d, lcm(l, d - 1));
        }
    }

    for (; dep <= numPrimes && m <= n / primes[dep] / primes[dep]; ++dep) {
        long p = primes[dep];
        // for (auto x : cs[dep])
        //     if (m % x == 0)
        //         continue;
        long newL = lcm(l, p - 1);

        dfs(dep + 1, newL, m * p);
    }
}

int main() {
    PrimeSeq gen;
    for (int i = 1; i <= numPrimes; ++i)
        primes[i] = gen.next();
    print("next prime: {}\n", gen.next());

    ans += 1 + 2;
    dfs(2, 1, 1); // do not search prime 2
    print("ans = {}\n", ans);

    return 0;
}
