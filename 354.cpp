#include "fmt/format.h"
#include "fmt/ostream.h"
#include <NTL/ZZ.h>
#include <algorithm>
using namespace fmt;
using namespace NTL;
using namespace std;

const int L = 4e7, numPrime = 2e6, maxRoot4 = 5.4e5;
const ZZ n{(long) 5e11};

bool chk[L + 10], o[L + 10];
long primes[numPrime];

long Root(ZZ n, int x) {
    // print("find root: {}, {}\n", n, x);
    long L = 0, R = conv<long>(SqrRoot(n)), m;
    for (; m = (L + R + 1) >> 1, L != R; )
        power_ZZ(m, x) <= n ? L = m : R = m - 1;
    return m;
}

long getCount(int p) {
    return upper_bound(primes + 1, primes + primes[0] + 1, p) - primes - 1;
}

long countWithout3(ZZ n) {
    long ret = 0;

    // ret += getCount(Root(n, 75 - 1));

    for (int i = 1; i <= primes[0] && power_ZZ(primes[i], 24) <= n; ++i)
        for (int j = 1; j <= primes[0] && power_ZZ(primes[i], 24) * power_ZZ(primes[j], 2) <= n; ++j)
            if (i != j)
                for (long x = 1, rem = conv<long>(SqrRoot(n / power_ZZ(primes[i], 24) / power_ZZ(primes[j], 2))); x <= rem; ++x)
                    ret += !o[x];
    for (int i = 1; i <= primes[0] && power_ZZ(primes[i], 14) <= n; ++i)
        for (int j = 1; j <= primes[0] && power_ZZ(primes[i], 14) * power_ZZ(primes[j], 4) <= n; ++j)
            if (i != j)
                for (long x = 1, rem = conv<long>(SqrRoot(n / power_ZZ(primes[i], 14) / power_ZZ(primes[j], 4))); x <= rem; ++x)
                    ret += !o[x];

    for (int i = 1; i <= primes[0] && primes[i] * primes[i] < maxRoot4; ++i) {
        for (int j = i + 1; j <= primes[0] && primes[i] * primes[j] < maxRoot4; ++j) {
            long rem = conv<long>(SqrRoot(n / power_ZZ(primes[i] * primes[j], 4)));
            if (i == 1 && j == 2)
                print("i = {}, j = {}, rem = {} \n", i, j, rem);

            for (long x = 1; x <= rem; ++x) {
                if (o[x])
                    continue;
                long lmt = rem / x;
                ret += getCount(lmt) - (primes[i] <= lmt) - (primes[j] <= lmt);
            }
        }
    }

    // print("n = {}, ret = {}\n", n, ret);
    return ret;
}

const int M = 1000000;
int cnt[M + 1];

int solve(int n) {
    int ret = 1;

    for (int i = 2; i <= n; ++i) {
        if (i * i > n)
            i = n;
        if (n % i == 0) {
            int e = 0;
            for (; n % i == 0; n /= i)
                ++e;
            if (i % 3 == 1) {
                ret *= e + 1;
            } else if (i % 3 == 2) {
                if (e % 2 != 0)
                    return 0;
            }
        }
    }
    return ret;
}

int main() {
    for (int a = 1; a * a <= M; ++a)
        for (int b = 0; a * a + a * b + b * b <= M; ++b)
            cnt[a * a + a * b + b * b] += 1;
    for (int i = 2; i <= M; ++i) {
        if (cnt[i] != solve(i)) {
            print("{}: {}, {}\n", i, cnt[i], solve(i));
            // return 0;
        }
    }
    // print("{}\n", cnt[7 * 7 * 5]);

    for (int i = 2; i <= L; ++i)
        if (!chk[i]) {
            for (int j = i; j <= L; j += i)
                chk[j] = true;
            if (i % 3 == 1) {
                primes[++primes[0]] = i;
                for (int j = i; j <= L; j += i)
                    o[j] = true;
            }
        }
    print("#primes = {}\n", primes[0]);

    ZZ bound = n * n / 3;
    long ans = countWithout3(bound) + countWithout3(bound / 3);
    // long end = conv<long>(n / 3);
    // for (long i = 1; ; ++i) {
    //     long current = countWithout3(n * n / 9 / i / i);
    //     if (i % 10 == 0)
    //         print("i = {}, val = {}, current = {}\n", i, n * n / 9 / i / i, current);
    //     ans += current;
    //     if (current == 0) {
    //         break;
    //     }
    // }
    print("ans = {}\n", ans);
    return 0;
}