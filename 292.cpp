#include "fmt/format.h"
using namespace fmt;

const int R_LMT = 1000;

int main() {
    for (long r = 2; r <= R_LMT; r += 2) {
        for (long a = 1; a <= 3 * r * r; ++a) {
            for (long b = r * r / a; a * b <= 3 * r * r; ++b) {
                long p = r * r * (a + b), q = a * b - r * r;
                if (q > 0 && p % q == 0) {
                    long c = p / q;
                    print("find {}, {}, {}\n", a + b, b + c, c + a);
                }
            }
        }
    }
    return 0;
}