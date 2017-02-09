#include "fmt/format.h"
#include <NTL/ZZ.h>
using namespace fmt;
using namespace NTL;

const long n = 1e16, N = n + 10;
const int m = 1e8, M = m + 10;

long f[M];

int main() {
    for (int i = (m | 1) - 2; i >= 0; i -= 2) {
        f[i] = (n / i / i + 3) / 4;
        for (int j = 3, T = m / i; j <= T; j += 2) {
            f[i] -= f[i * j];
        }
        // print("f[{}] = {}\n", i, f[i]);
    }

    long ans = f[1];
    PrimeSeq gen;
    for (int u; (u = gen.next()) < m; )
        if (u % 4 == 3)
            ans += f[u];
    print("ans = {}\n", ans);
    return 0;
}