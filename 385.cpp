#include <cstdio>
#include <map>
using namespace std;

const int n = 100;

typedef pair<int, int> P;

int main() {
    long ans = 0;
    for (int xa = -n; xa <= 0; ++xa)
        for (int xb = -n; xb <= n; ++xb)
            for (int ya = -n; ya <= n; ++ya)
                for (int yb = -n; yb <= n; ++yb) {
                    if (ya == 0 && yb == 0) continue;
                    int xc = -xa - xb, yc = -ya - yb;
                    int re = (xa * xa + xb * xb + xa * xb) - (ya * ya + yb * yb + ya * yb);
                    if (re != 39) continue;
                    int im = 2 * xa * ya + 2 * xb * yb + xa * yb + xb * ya;
                    if (im != 0) continue;
                    if (P(xa, ya) > P(xb, yb) || P(xb, yb) > P(xc, yc))
                        continue;
                    printf("(%d, %d), (%d, %d), (%d, %d)\n", xa, ya, xb, yb, xc, yc);
                    int A = (xa * yb + xb * yc + xc * ya) - (ya * xb + yb * xc + yc * xa);
                    ans += A > 0 ? A : -A;
                }
    printf("ans = %ld\n", ans / 2);
    return 0;
}
