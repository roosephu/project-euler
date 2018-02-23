#include "fmt/format.h"
#include <NTL/ZZ.h>
using namespace fmt;
using namespace std;
using namespace NTL;

namespace PE618 {
    const int n = 50000, N = n + 10;
    const int MOD = 1e9;

    long f[N];

    void main() {
        f[0] = 1;
        PrimeSeq gen;
        for (int p; (p = gen.next()) <= n; ) {
            for (int i = p; i <= n; ++i) {
                f[i] = (f[i] + f[i - p] * p) % MOD;
            }
        }

        long ans = 0;
        for (int i = 2, a = 1, b = 1; i <= 24; ++i) {
            int c = a + b;
            print("a = {}\n", a);
            ans += f[a];
            b = a;
            a = c;
        }
        print("ans = {}\n", ans % MOD);
    }
}

int main() {
    PE618::main();
    return 0;
}
