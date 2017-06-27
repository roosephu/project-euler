#include "fmt/format.h"
#include "fmt/ostream.h"
#include <NTL/ZZ_p.h>
#include <NTL/ZZ.h>
using namespace fmt;
using namespace NTL;

namespace PE603 {
    const int MOD = 1e9 + 7;
    const long n = 1e6;
    const long k = 1e12;

    int digits[n * 8];

    void main() {
        ZZ_p::init(ZZ(MOD));
        PrimeSeq gen;

        int mm = 0;
        for (int i = 1; i <= n; ++i) {
            int u = gen.next(), aux[13], length = 0;
            // u = 23;
            for (; u; u /= 10)
                aux[++length] = u % 10;
            for (; length; --length)
                digits[++mm] = aux[length];
        }
        print("m = {}\n", mm);

        ZZ m{mm};
        ZZ_p ans{0};
        ZZ_p ten{10};
        ZZ_p tmp1 = 1 - power(ten, -m);
        ZZ_p tmp2 = 1 - power(ten, -m * k);
        ZZ_p tmp3 = inv(tmp1);
        ZZ_p inv9 = inv(ZZ_p(9)), inv2 = inv(ZZ_p(2));
        print("tmp1 = {}, tmp2 = {}\n", tmp1, tmp2);
        for (int i = 1; i <= m; ++i) {
            if (i % 100000 == 0)
                print("{}\n", i);
            ans += ZZ_p(digits[i]) * inv9 * (
                power(ten, m * k + 1 - i) * (
                    tmp2 * tmp3 * i
                    + tmp2 * tmp3 * tmp3 * (1 - tmp1) * mm
                    - (1 - tmp2) * tmp3 * k * mm
                )
                - inv2 * k * (k - 1) * mm
                - ZZ_p(k) * i
            );
        }
        print("ans = {}\n", ans);
    }
}

int main() {
    PE603::main();
    return 0;
}