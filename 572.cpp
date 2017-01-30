#include "fmt/format.h"
using namespace fmt;

const int n = 200, N = n + 1;

int max(int a, int b) {
    return a > b ? a : b;
}

bool fit(int x) {
    return -n <= x && x <= n;
}

int main() {
    int cnt = 0, ans = 0;
    for (int v1 = -N; v1 <= N; ++v1)
        for (int v2 = -N; v2 <= N; ++v2)
            for (int v3 = -N; v3 <= N; ++v3) {
                int p = max(max(abs(v1), abs(v2)), abs(v3));
                if (p == 0) continue;
                int T = N / p;
                for (int u1 = -T; u1 <= T; ++u1)
                    for (int u2 = -T; u2 <= T; ++u2)
                        for (int u3 = -T; u3 <= T; ++u3) {
                            int dot = v1 * u1 + v2 * u2 + v3 * u3;
                            if (dot != 1) continue;
                            ++cnt;
                            int q = max(max(abs(u1), abs(u2)), abs(u3));
                            if (p * q <= n) ++ans;
                            if (fit(v1 * u2) && fit(v1 * u3) && fit(v2 * u1) && fit(v2 * u3) && fit(v3 * u1) && fit(v3 * u2)
                                && fit(v1 * u1 - 1) && fit(v2 * u2 - 1) && fit(v3 * u3 - 1))
                                ++ans;
                        }
            }
    print("cnt = {}, ans = {}\n", cnt, ans / 2 + 2); // why / 2 + 2 can work?
    return 0;
}