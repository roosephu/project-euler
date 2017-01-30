#include "fmt/format.h"
using namespace fmt;

const long n = 3969, N = n + 10;
const int m = 70, M = m + 10;

long f[M];

int main() {
    for (int i = m; i; --i) {
        f[i] = (n / i / i + 3) / 4;
        for (int j = 3; j * j <= n / i / i; j += 2) {
            f[i] -= f[i * j];
        }
        print("f[{}] = {}\n", i, f[i]);
    }
    print("ans = {}\n", f[1]);
    return 0;
}