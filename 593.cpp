#include "fmt/format.h"
#include <NTL/ZZ.h>
using namespace fmt;
using namespace NTL;

namespace PE593 {
    const int n = 1e7, N = n + 10, offset = 32768, K = 1e5;
    const long MOD = 10007;
    int S[N];
    int bit[offset << 1];

    void update(int x, int delta) {
        for (x += offset; x; x >>= 1)
            bit[x] += delta;
    }

    int query(int rank) {
        int x = 1;
        for (; x < offset; ) {
            x <<= 1;
            if (bit[x] < rank) {
                rank -= bit[x];
                x |= 1;
            }
        }
        return x - offset;
    }

    void main() {
        PrimeSeq gen;
        for (int i = 1; i <= n; ++i)
            S[i] = PowerMod(gen.next() % MOD, i, MOD);
        for (int i = n; i; --i)
            S[i] += S[i / 10000 + 1];

        long ans = 0;
        for (int i = 1; i <= n; ++i) {
            // print("> {}\n", S[i]);
            update(S[i], +1);
            if (i >= K) {
                ans += query(K / 2) + query(K / 2 + 1);
                // if (i == K) {
                //     print("{}\n", query(K / 2) + query(K / 2 + 1));
                // }
                update(S[i - K + 1], -1);
            }
        }
        print("ans = {}\n", ans);
    }
}

int main() {
    PE593::main();
    return 0;
}
