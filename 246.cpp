#include "fmt/format.h"
#include <cmath>
using namespace fmt;

const long A = 7500 * 7500, B = 7500 * 7500 - 5000 * 5000;

int main() {
    const double eb = sqrt(B), ea = sqrt(A);
    const double lmt = acos(-1) / 4;

    long ans = 0;
    for (int x = 0; x <= 30000; ++x) {
        bool b = false;
        for (int y = 0; ; ++y) {
            double ratio = (double) x * x / A + (double) y * y / B;
            if (ratio <= 1) {
                continue;
            }
            double tc = atan2(y / eb, x / ea), td = acos(1. / sqrt(ratio));
            double t1 = tc - td, t2 = tc + td;
            double w1 = atan2(y - eb * sin(t1), x - ea * cos(t1));
            double w2 = atan2(y - eb * sin(t2), x - ea * cos(t2));
            if (fabs(w1 - w2) >= lmt) {
                b = true;
                ans += 2 + 2 * (x && y);
            } else {
                if (y != 0)
                    print("x = {}, y = {}, t1 = {:.9f}, t2 = {:.9f}, ans = {}\n", x, y, t1, t2, ans);
                break;
            }
        }
        // if (!b) {
        //     break;
        // }
    }
    print("ans = {}\n", ans);
    return 0;
}