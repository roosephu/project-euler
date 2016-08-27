#include "fmt/format.h"
#include "fmt/ostream.h"
#include <map>
#include <NTL/lzz_p.h>
using namespace std;
using namespace fmt;
using namespace NTL;

const long n = 1e12, M = 1e6 + 10, MOD = 1e9;

long primes[M], basis[M * 2];
map<long, pair<zz_p, zz_p>> f;

int main() {
    long R = SqrRoot(n);
    zz_p::init(MOD * 2);
    for (long i = 2; i * i <= n; ++i)
        if (ProbPrime(i))
            primes[++primes[0]] = i;

    int cnt = 0;
    for (long i = 1; n / i > R; ++i)
        basis[++cnt] = n / i;
    for (int i = R; i; --i)
        basis[++cnt] = i;

    for (int i = 1; i <= cnt; ++i) {
        long x = basis[i];
        f[x] = {zz_p(x - 1), zz_p(x - 1) * (x + 2)};
    }
    zz_p ans{0};
    for (long x = 2; x <= R; ++x) {
        // if (x % 1000 == 0)
        if (ProbPrime(x)) {
            print("{}\n", x);
            ans += x * f[n].first;
            zz_p old = f[n].first;
            for (int i = 1; i <= cnt; ++i) {
                long y = basis[i];
                if (x * x > y)
                    break;
                auto a = f[y / x];
                auto b = f[x - 1];
                f[y].first  -=  a.first  - b.first;
                f[y].second -= (a.second - b.second) * x;
            }
            ans -= x * f[n].first;
            // print("x = {}, delta = {}, old = {}\n", x, rep(old) - rep(f[n].first), old);
        }
    }
    ans += rep(f[n].second) / 2;

    print("ans = {}, |f| = {}\n", ans, f.size());
    return 0;
}