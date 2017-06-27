#include "fmt/format.h"
#include <map>
using namespace fmt;
using namespace std;

namespace PE597 {
    const int n = 13;
    const int DELTA = 40, L = 1800;

    map<int, double> f[1 << n][2];

    void main() {
        f[0][0][0] = 1;
        for (int S = 0; S < (1 << n) - 1; ++S) {
            for (int b = 0; b < 2; ++b) {
                int d[20] = {-1}, m = 0;
                for (int i = 0; i < n; ++i) {
                    if (~S >> i & 1) {
                        d[++m] = i;
                    }
                }
                d[m + 1] = d[m];
                for (auto it : f[S][b]) {
                    for (int i = 1; i <= m; ++i) {
                        int x = d[i], combined = x - d[i - 1], next = d[i + 1] - x;
                        int swapped = combined * !!next; // combined * next;
                        int distance = i == m ? L - x * DELTA : (DELTA * next);
                        int sum = it.first + combined * distance;

                        f[S | 1 << x][(b + swapped) % 2][sum] += it.second * distance / sum;
                    }
                }
            }
        }

        double ans = 0;
        for (auto it : f[(1 << n) - 1][0])
            ans += it.second;
        print("ans = {:0.10f}\n", ans);
    }
}

int main() {
    PE597::main();
    return 0;
}