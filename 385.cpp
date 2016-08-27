#include <set>
#include <tuple>
#include "fmt/format.h"
using namespace std;
using namespace fmt;

const long n = 1e9, L = n * 4;
typedef pair<long, long> P;

set<tuple<long, long, long, long>> f;
long ans = 0;

void generate(long xa, long ya, long xb, long yb) {
    if (xa > L || xa < -L) return;
    tuple<long, long, long, long> S(xa, ya, xb, yb);
    if (f.count(S) == 0) {
        f.insert(S);
        long Xa = (xa - xb) / 2, Ya = (ya - yb) / 2;
        long xc = -Xa - xb, yc = -Ya - yb;
        if (-n <= Xa && Xa <= n && -n <= xb && xb <= n && -n <= xc && xc <= n &&
            -n <= Ya && Ya <= n && -n <= yb && yb <= n && -n <= yc && yc <= n &&
            P(Xa, Ya) <= P(xb, yb) && P(xb, yb) <= P(xc, yc)) {
            print("({}, {}), ({}, {}), ({}, {}): 2x + y = ({}, {}), y = ({}, {})\n", Xa, Ya, xb, yb, xc, yc, 2 * Xa + xb, 2 * Ya + yb, xb, yb);
            // print("({}, {}), ({}, {}) => ({}, {})\n", xa, ya, xb, yb, xa * xa - ya * ya + 3 * (xb * xb - yb * yb), xa * ya * 2 + 3 * xb * yb * 2);
            long A = (Xa * yb + xb * yc + xc * Ya) - (Ya * xb + yb * xc + yc * Xa);
            ans += A > 0 ? A : -A;
        }

        generate(xa, -ya, xb, -yb);
        generate(-xa, ya, -xb, yb);
        generate(-xa, -ya, -xb, -yb);
        generate(2 * xa + 3 * yb, 2 * ya - 3 * xb, 2 * xb - ya, 2 * yb + xa);
        generate(2 * xa - 3 * yb, 2 * ya + 3 * xb, 2 * xb + ya, 2 * yb - xa);
    }
}

int main() {
    generate(12, 3, 4, -3);
    // generate(84, -24, 14, 48);
    generate(12, 0, 2, 0);
    // for (int xa = -n; xa <= 0; ++xa)
    //     for (int xb = -n; xb <= n; ++xb)
    //         for (int ya = -n; ya <= n; ++ya)
    //             for (int yb = -n; yb <= n; ++yb) {
    //                 if (ya == 0 && yb == 0) continue;
    //                 int xc = -xa - xb, yc = -ya - yb;
    //                 int re = (xa * xa + xb * xb + xa * xb) - (ya * ya + yb * yb + ya * yb);
    //                 if (re != 39) continue;
    //                 int im = 2 * xa * ya + 2 * xb * yb + xa * yb + xb * ya;
    //                 if (im != 0) continue;
    //                 if (P(xa, ya) > P(xb, yb) || P(xb, yb) > P(xc, yc))
    //                     continue;
    //                 print("({}, {}), ({}, {}), ({}, {}): 2x + y = ({}, {}), y = ({}, {})\n", xa, ya, xb, yb, xc, yc, 2 * xa + xb, 2 * ya + yb, xb, yb);
    //                 int A = (xa * yb + xb * yc + xc * ya) - (ya * xb + yb * xc + yc * xa);
    //                 ans += A > 0 ? A : -A;
    //             }
    print("ans = {}\n", ans);
    return 0;
}
