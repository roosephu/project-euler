#include "fmt/format.h"
#include <cmath>
using namespace std;
using namespace fmt;

const int n = 1000000, N = n + 10;

double f[N];

int main() {
    double S = 0;
    for (int i = 1; i <= n; ++i) {
        double L = log(i);
        S = S + L;
        f[i] = S - i * L;
    }
    double ans = 0;
    for (int k = 1; k <= n; ++k) {
        ans += exp(f[n] - f[k] - f[n - k]);
        // if (k <= 100)
            // print("{:.6f}\n", exp(f[n] - f[k] - f[n - k]));
    }
    print("ans = {:.4f}\n", ans);
    return 0;
}