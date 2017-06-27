#include "fmt/format.h"
#include <NTL/ZZ.h>
using namespace fmt;
using namespace NTL;

namespace PE604 {
    const long M = 3e6;
    const long N = 1e18;

    long phi[M + 1];

    void main() {
        PrimeSeq gen;
        long ans = 1, rem = N;

        for (int i = 1; i <= M; ++i)
            phi[i] = i;
        for (int p; (p = gen.next()) <= M; ) {
            for (int i = p; i <= M; i += p) {
                phi[i] = phi[i] / p * (p - 1);
            }
        }

        for (int x = 2; x <= M; ++x) {
            long v = x * phi[x] / 2;

            if (rem > v) {
                rem -= v;
                ans += phi[x];
            } else {
                print("rem = {}, ans = {}\n", rem, ans);
                for (int s = 1; s <= x / 2; ++s) {
                    if (GCD(s, x) == 1) {
                        if (rem >= x) {
                            rem -= x;
                            ans += 2;
                        } else if (s <= rem && x - s <= rem) {
                            rem -= x - s;
                            ans += 1;
                        }
                    }
                }

                break;
            }
        }
        print("ans = {}\n", ans);
    }
}

int main() {
    PE604::main();
    return 0;
}