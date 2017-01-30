#include "fmt/format.h"
using namespace fmt;

const int n = 1000, N = n + 10;

// double p[N][N], q[N][N];
// int w[N][N];

double compute(int n, double pa, double pc) {
    double wa = 0.3, wb = 0.4, wc = 0.3;
    // double pb = 1 - 1. / 2 / (n - 2) - 1. / 4;
    double pb = 1 - 1. / 3 / (n - 2) - 1. / 6;
    for (int T = 0; T <= 10000; ++T) {
        double qa = wa * pa + wb * 1 / 3 / (n - 2);
        // double qa = wa * pa + wb * 1 / 2 / (n - 2);
        double qb = wa * (1 - pa) + wb * pb + wc * (1 - pc);
        // double qc = wc * pc + wb / 4;
        double qc = wc * pc + wb / 6;
        wa = qa, wb = qb, wc = qc;
    }
    wa /= 4;
    wb /= 4 * (n - 2);
    wc /= (n - 2) * (n - 2);
    double ans = 0;
    for (int i = 1; i <= n; ++i) {
        int x = (i * i - 1) / n + 1;
        int y = i * i - (x - 1) * n;
        int d = (x > 1) + (y > 1) + (x < n) + (y < n);
        if (d == 2) ans += wa;
        if (d == 3) ans += wb;
        if (d == 4) ans += wc;
    }
    print("wa = {:6f}, wb = {:6f}, wc = {:6f}\n", wa * n * n, wb * n * n, wc * n * n);
    return ans;
}

int main() {
    // for (int i = 1; i <= n; ++i)
    //     for (int j = 1; j <= n; ++j) {
    //         w[i][j] = (i > 1) + (j > 1) + (i < n) + (j < n);
    //         p[i][j] = 1.;
    //     }
    // for (int T = 0; T < 1000; ++T) {
    //     for (int i = 1; i <= n; ++i)
    //         for (int j = 1; j <= n; ++j)
    //             q[i][j] = 0;
    //     for (int i = 1; i <= n; ++i)
    //         for (int j = 1; j <= n; ++j) {
    //             double d = w[i][j];
    //             double p1 = 1, p2 = 0;
    //             // if (i == X && j == Y)
    //             //     p1 = 0, p2 = 1;
    //             q[i][j] += p[i][j] * (p1 / (d + 1) + p2 / 2);
    //             q[i + 1][j] += p[i][j] * (p1 / (d + 1) + p2 / 2 / d);
    //             q[i - 1][j] += p[i][j] * (p1 / (d + 1) + p2 / 2 / d);
    //             q[i][j + 1] += p[i][j] * (p1 / (d + 1) + p2 / 2 / d);
    //             q[i][j - 1] += p[i][j] * (p1 / (d + 1) + p2 / 2 / d);
    //         }
    //     for (int i = 1; i <= n; ++i)
    //         for (int j = 1; j <= n; ++j)
    //             p[i][j] = q[i][j];
    //     double ans = 0;
    //     for (int i = 1; i <= n; ++i) {
    //         int x = (i * i - 1) / n + 1;
    //         int y = i * i - (x - 1) * n;
    //         ans += p[x][y];
    //         // print("{} {} = {:.14f}\n", x, y, p[x][y]);
    //     }
    //     for (int i = 1; i <= n; ++i) {
    //         for (int j = 1; j <= n; ++j) {
    //             print("{:.3f} ", p[i][j]);
    //         }
    //         print("\n");
    //     }
    //     // print("ans = {:.14f}, compute = {:.14f}\n", ans / n / n, compute(n, 0.5, 1 - 0.5 / (n - 2)));
    //     print("ans = {:.14f}, compute = {:.14f}\n", ans / n / n, compute(n, 1. / 3, 1 - 0.8 / (n - 2)));
    // }
    // print("ans = {:.14f}\n", compute(n, 1. / 3, 1 - 0.8 / (n - 2)));
    print("ans = {:.14f}\n", compute(n, 0.5, 1 - 0.5 / (n - 2)));

    // double s = 0;
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n; ++j) {
    //         print("{:.6f} ", p[i][j]);
    //         s += p[i][j];
    //     }
    //     print("\n");
    // }
    return 0;
}