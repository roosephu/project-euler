#include "fmt/format.h"
#include <algorithm>
using namespace fmt;
using namespace std;

namespace PE600 {
    const long n = 55106;
    long f[100000];

    void main() {
        for (int b = 0; b <= n / 2; ++b) {
            if (b % 100 == 0) {
                print("{}\n", b);
            }
            for (int s = 0; s <= b * 2 && 2 * b + s <= n; ++s) {
                f[2 * b + s] += min(s, 2 * b - s) + 1;
            }
        }
        for (int i = 0; i < n; ++i) {
            f[i + 1] += f[i];
            // print("{}: {}\n", i, f[i]);
        }

        long ans = 0;
        for (int a = 0; 2 * a <= n - 6; ++a) {
            ans += f[n - 6 - 2 * a] * (1 + !!a);
        }
        print("mid = {}\n", ans);
        ans += (n / 6) * 2;
        ans += (n / 3) * (n / 3 - 1) / 2 * 2;
        ans += (n / 2) * (n / 2 - 1) * (n / 2 - 2) / 6;

        ans += f[n - 6] * 3;
        for (int b = 1; 2 * b < n / 2; ++b) {
            ans += (n / 2 - 2 * b) * 3;
        }
        print("{}, {}\n", ans % 12, ans / 12);
    }
}

int main() {
    PE600::main();
    return 0;
}