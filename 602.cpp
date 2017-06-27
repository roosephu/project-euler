#include "fmt/format.h"
#include <NTL/ZZ.h>
using namespace fmt;
using namespace NTL;

namespace PE602 {
    const int n = 1e7, k = 4e6;
    const int MOD = 1e9 + 7;

    void main() {
        long ans = 0, binomial = 1;
        for (int i = 0; i <= k; ++i) {
            ans += (i & 1 ? -1 : 1) * PowerMod(k - i, n, MOD) * binomial % MOD;
            binomial = binomial * (n + 1 - i) % MOD * InvMod(i + 1, MOD) % MOD;
        }
        print("ans = {}\n", (ans % MOD + MOD) % MOD);
    }
}

int main() {
    PE602::main();
    return 0;
}