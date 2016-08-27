#include "fmt/format.h"
#include <algorithm>
using namespace fmt;
using namespace std;

const int R_LMT = 1000;

int main() {
    long ans = 0;
    for (long r = 2; r <= 2 * R_LMT; r += 2) {
        print("r = {}\n", r);
        for (long a = 1; a * a <= 3 * r * r; ++a) {
            for (long b = max(r * r / a, a); a * b <= 3 * r * r; ++b) {
                long p = r * r * (a + b), q = a * b - r * r;
                if (q <= 0)
                    continue;
                if (p < b * q)
                    break;
                if (p % q == 0) {
                    long c = p / q;
                    // print("find {}, {}, {}\n", a + b, a + c, b + c);
                    long perimeter = 2 * (a + b + c);

                    ans += perimeter;
                }
            }
        }
    }
    print("ans = {}\n", ans);
    return 0;
}