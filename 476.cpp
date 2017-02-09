#include "fmt/format.h"
#include <cmath>
#include <tuple>
using namespace fmt;
using namespace std;

typedef double real;

const real pi = acos(-1);

void update(real &m1, real &m2, real x) {
    if (x > m1) {
        m2 = m1, m1 = x;
    } else if (x > m2) {
        m2 = x;
    }
}

real calc(real a, real b, real c) {
    real p = (a + b + c) / 2;
    real R = sqrt(p * (p - a) * (p - b) * (p - c)) / p;
    vector<real> candidates;

    real m1 = 0, m2 = 0;
    for (int _ = 0; _ < 3; ++_) {
        real t = p - c;
        real sin_theta = R / hypot(t, R);
        real r = R * (1 - sin_theta) / (1 + sin_theta);
        real w = R * r / (R + r + 2 * sqrt(R * r));
        update(m1, m2, r);
        update(m1, m2, w);
        update(m1, m2, r * (1 - sin_theta) / (1 + sin_theta));

        real x = a; a = b, b = c, c = x;
    }

    return pi * (R * R + m1 * m1 + m2 * m2);
}

int main(int argc, char **argv) {
    const int n = 1803;
    real ans = 0; int cnt = 0;
    for (int a = 1; a <= n; ++a) {
        print("{}\n", a);
        for (int b = a; a + b <= n; ++b) {
            for (int c = b; c < a + b && c <= n; ++c) {
                ans += calc(a, b, c);
                cnt += 1;
            }
        }
    }
    print("ans = {:15f}, cnt = {}\n", ans / cnt, cnt);

    return 0;
}
