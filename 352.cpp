#include "fmt/format.h"
#include <algorithm>
using namespace std;
using namespace fmt;

const int n = 10000, N = n + 10;

double f[N], g[N], P[N];

int main() {
    double ans = 0;
    for (int p100 = 1; p100 <= 50; ++p100) {
        double p = p100 / 100.;
        f[1] = 1;
        g[1] = 0;

        P[0] = 1;
        for (int i = 1; i <= n; ++i) {
            P[i] = P[i - 1] * (1 - p);
        }
        for (int i = 2; i <= n; ++i) {
            g[i] = f[i] = i;
            for (int k = 1; k < i; ++k) {
                double p_pos = (1 - P[k]) / (1 - P[i]);
                g[i] = min(g[i], 1 + p_pos * (f[i - k] + g[k]) + (1 - p_pos) * g[i - k]);
            }
            for (int k = 1; k <= i; ++k) {
                double p_pos = 1 - P[k];
                f[i] = min(f[i], 1 + p_pos * (g[k] + f[i - k]) + (1 - p_pos) * f[i - k]);
            }
        }
        ans += f[n];
        print("p = {}, ans = {:.6f}\n", p, ans);
    }
    return 0;
}