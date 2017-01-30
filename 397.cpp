#include "fmt/format.h"
using namespace std;
using namespace fmt;

const int K = 10, X = 200;

bool test(long k, long a, long b, long c) {
    long v = k * k + (b + c) * (b + a);
    if (v * (b - c) * (b - a) < 0) return false;
    return v * v == k * k * (a - c) * (a - c);
}

int main() {
    long ans = 0;
    for (int k = 1; k <= K; ++k)
        for (int a = -X; a <= X; ++a)
            for (int b = a + 1; b <= X; ++b)
                for (int c = b + 1; c <= X; ++c) {
                    if (test(k, a, b, c) || test(k, a, c, b) || test(k, b, a, c)) {
                        ++ans;
                    }
                    // ans += test(k, a, b, c) + test(k, a, c, b) + test(k, b, a, c);
                }
    print("ans = {}\n", ans);
    return 0;
}