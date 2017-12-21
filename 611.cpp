#include "fmt/format.h"
#include <NTL/ZZ.h>
using namespace fmt;
using namespace NTL;

namespace PE611 {
    const int n = 1000000;

    int check(int n) {
        while (n % 2 == 0) {
            n /= 2;
        }
        int cnt = 1;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                int e = 0;
                for (; n % i == 0; ++e)
                    n /= i;
                if (i % 4 == 3 && e % 2 != 0)
                    return 0;
                if (i % 4 == 1)
                    cnt *= e + 1;
            }
        }
        if (n != 1) {
            if (n % 4 == 3)
                return 0;
            cnt *= 2;
        }
        return cnt % 4 == 2 || cnt % 4 == 3;
    }

    void main() {
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (check(i)) {
                // print("{}\n", i);
                ans += 1;
            }
        }
        print("ans = {}\n", ans);
    }
}

int main() {
    PE611::main();
    return 0;
}
