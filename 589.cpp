#include "lib.h"

namespace PE589 {
    const long L = 30, R = 60;

    double f[100];

    double F(int L, int R) {
        for (int T = 0; ; ++T) {
            double diff = 0;
            for (int x = 0; x <= R + 5; ++x) {
                double e = 5 * (R - L + 1) * (R - L + 1);
                for (int a = L; a <= R; ++a) {
                    for (int b = L; b <= R; ++b) {
                        if (a + 5 < x) {
                            e += a;
                        } else if (a <= x + b) {
                            e += a + f[x + b - a];
                        } else {
                            e += x + b + f[a - x - b];
                        }
                    }
                }
                double fx = e / (R - L + 1) / (R - L + 1);
                diff = max(diff, abs(f[x] - fx));
                f[x] = fx;
            }
            if (diff < 1e-6) {
                print("diff = {:.3f}, T = {}, ans = {}\n", diff, T, f[0] - 5);
                break;
            }
            // print("diff = {:.3f}, ans = {:.3f}\n", diff, f[0]);
        }
        return f[0] - 5;
    }

    void main() {
        double ans = 0;
        long k = 5;
        for (int R = 2; R <= k; ++R) {
            for (int L = 1; L < R; ++L) {
                ans += F(L, R);
            }
        }
        print("ans = {}\n", ans);
    }
}

int main() {
    PE589::main();
    return 0;
}
