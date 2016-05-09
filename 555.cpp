#include <cstdio>
using namespace std;

const int m = 1000000, K = 1000000;

long sum(long s, long k) {
    return (2 * m - 4 * s + 2 * k - (k - s - 1)) * (k - s) / 2;
}

int main() {
    long ans = 0;
    for (int k = 2; k <= K; ++k) {
        // for (int s = 1; s < k; ++s) {
            // if (s % (k - s) != 0)
            //     continue;
        for (int s = 1; s * s <= k; ++s) {
            if (k % s == 0) {
                ans += sum(k - s, k);
                if (s != 1 && s * s != k)
                    ans += sum(k - k / s, k);
            }
            // for (int i = 0; i < k - s; ++i) {
            //     int t = 2 * s + i - k;
            //     ans += m - t;
            // }
            // for (int i = m; i > m - s; --i) {
            //     int v = i + k;
            //     if (v > m + s)
            //         v -= 2 * s;
            //     else if (v > m)
            //         v = f[v - s];
            //     else
            //         v = f[f[v]];
            //     f[i] = v;
            //     if (i == v)
            //         ans += i;

            //     if (v != (m + k - 2 * s - (m - i) % (k - s)))
            //         printf("xxxx\n");
            //     if (k == 29 && s == 26) {
            //         printf("%d: %d\n", i, v);
            //     }
            // }
        }
    }
    printf("ans = %ld\n", ans);
    return 0;
}
