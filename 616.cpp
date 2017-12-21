#include "fmt/format.h"
#include <NTL/ZZ.h>
using namespace std;
using namespace fmt;
using namespace NTL;

/*
 * (2, a, b) -> (2, a^b) -> (2^{a^b}) -> (2^{a^{b-1}}, a) -> (2, a, a, b - 1)
 * (2, 2, 3) -> (2, 2, 2, 2) -> (2, 2, 4) -> (2, 2, 2, 3) -> (2, 2, 8)
 */
namespace PE616 {
    const long n = 1e12, N = 1e6 + 10;

    bool b[N];

    void main() {
        PrimeSeq gen;
        long ans = 0;
        for (long u = 2; u <= 1e6; ++u) {
            if (b[u]) {
                continue;
            }
            int e = 2;
            long power = u * u;
            for (; power <= n; ) {
                if (power <= N)
                    b[power] = true;
                if (!ProbPrime(e) || !ProbPrime(u)) {
                    if (e * u > 8) {
                        ans += power;
                    } else {
                        print("{}^{} = {}\n", u, e, power);
                    }
                }
                power *= u;
                ++e;
            }
        }
        print("ans = {}\n", ans);
    }
}

int main() {
    PE616::main();
    return 0;
}
