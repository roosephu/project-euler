#include "fmt/format.h"
using namespace fmt;

namespace PE595 {
    const int n = 52, N = n + 10;

    double f[N][N], g[N];

    void main() {
        f[1][1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                f[i][j] = f[i - 1][j] / i + f[i - 1][j - 1] * (j - 1) / i + (j ? f[i - 1][j - 2] * (i + 1 - j) / i : 0);
                // print("{} ", f[i][j]);
            }
            // print("\n");
        }
        g[1] = 1;
        for (int i = 2; i <= n; ++i) {
            g[i] = 1;
            for (int j = 2; j < i; ++j) {
                g[i] += g[j] * f[i][j];
            }
            g[i] /= 1 - f[i][i];
            print("{:2.8f}\n", g[i] - 1);
        }
    }
}

int main() {
    PE595::main();
    return 0;
}
