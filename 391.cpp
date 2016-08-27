#include "fmt/format.h"
#include <algorithm>
using namespace fmt;
using namespace std;

const int n = 1000, N = n + 10;

int F[2][N][N];

int compute(int n) {
    n += 1;

    int (*f)[N] = F[0], (*g)[N] = F[1];
    for (int s = 0; s <= n + 1; ++s)
        for (int x = 0; x <= n; ++x)
            if (s + x >= n)
                f[s][x] = 0;
            else
                f[s][x] = s + x;

    for (int h = 1; h <= n; ++h) {
        for (int s = 0; s <= n - h; ++s) {
            for (int x = 0; x <= n; ++x) {
                int y = f[s + 1][x];
                g[s][x] = f[s][y];
            }
        }
        swap(f, g);
    }
    return f[0][0];
}

int main() {
    long ans = 0;
    for (int i = 1; i <= n; ++i) {
        long x = compute(i);
        ans += x * x * x;
        print("{}: {}\n", i, x);
    }
    print("ans = {}\n", ans);
    return 0;
}