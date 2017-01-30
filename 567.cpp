#include "fmt/format.h"
#include <cmath>
using namespace std;
using namespace fmt;

const double eps = 1e-20;
const long n = 6;
const double pi = acos(-1);

double J_A(long n) {
    double t = 0, v = 0;
    for (int i = n / 2; i; --i) {
        // v = v * (n + 1 - i) / i / 4;
        v += log(n + 1 - i) - log(i);
    }
    v -= log(2) * n;
    // v = C(n, n / 2) / 2^n

    double v1 = v;
    for (int i = n / 2; i; --i) {
        t += exp(v1) / i;
        v1 += log(i) - log(n + 1 - i);
        if (v1 < -60)
            break;
    }
    double v2 = v;
    for (int i = n / 2 + 1; i <= n; ++i) {
        v2 += log(n + 1 - i) - log(i);
        if (v2 < -60)
            break;
        t += exp(v2) / i;
    }

    return t;
}

double H(long n) {
    if (n > 10000) {
        return 0.577215664901532 + log(n) + 0.5 / n;
    }
    double ret = 0;
    for (int i = 1; i <= n; ++i) {
        ret += 1. / i;
    }
    return ret;
}

double H2(long n) {
    if (n > 100000)
        return pi * pi / 6 - 1. / n;
    double ret = 0;
    for (int i = 1; i <= n; ++i)
        ret += 1. / i / i;
    return ret;
}

int main() {

    double ans1 = 0, ans2 = 0;
    long L1 = min(30000l, n);

    for (int i = 1; i <= L1; ++i) {
        // if (i % 1000 == 0)
            // print("i = {} J_A = {:}\n", i, J_A(i) - 2. / i * (1 + 1. / i));
        ans1 += J_A(i);
    }
    ans1 += 2 * (H(n) + H2(n)) - 2 * (H(L1) + H2(L1));

    // for (int i = 1; i <= n; ++i) {
    //     double v = 1;
    //     for (int j = 1; j <= i; ++j) {
    //         v = v * (i + 1. - j) / j;

    //         // ans += 1. / v / j;
    //         ans += pow(2, -i) * v / j;
    //     }
    // }

    // J_B, i = 1
    ans2 += H(n);

    // J_B, i = 2
    ans2 += 1 - 1. / n;

    long L2 = min(10000000l, n);
    double tmp = 0;
    for (int i = 3; i <= L2; ++i) {
        double v = 1. / i;
        for (int j = i; j <= n && v > eps; ++j) {
            // if (i == L2)
                // print("{} {}\n", i, j);
            tmp += v;

            v = v * (j + 1 - i) / (j + 1);
        }
    }
    ans2 += tmp;

    // J_B, i > 1e7
    ans2 += 1. / (L2 + 1) - 1. / (n + 1);
    ans2 += H(n) - H(L2);

    print("ans = {:.8f}\n", ans2 + ans1);

    return 0;
}