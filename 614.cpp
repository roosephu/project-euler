#include "fmt/format.h"
#include <algorithm>
using namespace fmt;
using namespace std;

namespace PE614 {
    const int MOD = 1e9 + 7;
    const int n = 1, N = n * 1.1;

    long p[N / 4], q[N], a[N];

    void main() {
        p[0] = 1;
        for (int k = 1; k * (3 * k - 1) / 2 <= n / 4; ++k) {
            int v = k & 1 ? MOD - 1 : 1;
            p[k * (3 * k - 1) / 2] = v;
            p[k * (3 * k + 1) / 2] = v;
        }
        for (int i = 1; i <= n / 4; ++i) {
            if (i % 100000 == 0)
                print("1: {}\n", i);
            long v = 0;
            for (int k = 1; k * k <= i; ++k)
                v += k & 1 ? p[i - k * k] : MOD - p[i - k * k];
            p[i] = (p[i] + v * 2) % MOD;
        }

        for (int i = 1; i <= n / 4; ++i) {
            // print("{}: {}\n", i, p[i]);
            p[i] = (p[i] + p[i - 1]) % MOD;
        }
        q[0] = 1;
        long ans = p[n / 4] - 1;
        for (int t = 1; t * t <= n; ++t) {
            if (t % 10 == 0)
                print("2: {}\n", t);
            for (int i = (t - 1) * (t - 1); i < t * t; ++i) {
                a[i] = q[i];
                q[i] = 0;
            }
            for (int i = t * t; i <= n; ++i) {
                a[i] = q[i];
                q[i] = ((i >= 2 * t ? q[i - 2 * t] : 0) + a[i - 2 * t + 1]) % MOD;
                ans += q[i] * p[(n - i) / 4] % MOD;
            }
        }
        print("ans = {}\n", ans % MOD);
    }
}

int main() {
    PE614::main();
    return 0;
}
