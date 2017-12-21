#include "fmt/format.h"
#include <NTL/ZZ.h>
using namespace fmt;
using namespace NTL;

namespace PE609 {
    const int n = 1e8, N = n + 10;
    const int MOD = 1e9 + 7;

    int pi[N], P[100];

    void main() {
        PrimeSeq gen;
        for (int u; (u = gen.next()) < n; )
            pi[u] = 1;
        for (int i = 1; i <= n; ++i) {
            pi[i] += pi[i - 1];
            if (i % 1000000 == 0) {
                print("current = {}\n", i);
            }
            for (int w = i, cnt = 0; w; w = pi[w]) {
                cnt += pi[w] == pi[w - 1];
                if (w != i) {
                    if (cnt == 100) {
                        print("XXX\n");
                        return;
                    }
                    P[cnt] += 1;
                }
            }
        }
        long ans = 1;
        for (int i = 0; i <= 100; ++i) {
            if (P[i] == 0) {
                break;
            }
            ans = ans * (P[i] % MOD) % MOD;
        }
        print("ans = {}\n", ans);
    }
}

int main() {
    PE609::main();
    return 0;
}
