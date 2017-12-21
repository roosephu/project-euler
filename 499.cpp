#include "fmt/format.h"
#include <cmath>
using namespace fmt;
using namespace std;

namespace PE499_1 {
    const int K = 10, m = 6;
    double a[K], b[K], learning_rate = 0.01;

    double eval(double x) {
        if (x * m > 1)
            return 1;
        double ret = 0;
        for (int i = 0; i < K; ++i)
            ret += a[i] * pow(x, b[i]);
        return max(min(ret, 1.), 0.);
    }

    double GT(double x) {
        double ret = 0, coef = 1;
        for (int i = 0; i <= 20; ++i) {
            coef /= 2;
            ret += coef * eval(1 / (x + (1 << i)));
        }
        return ret;
    }

    void update(double delta, double x) {
        delta *= learning_rate;
        double L = log(x);
        for (int i = 0; i < K; ++i) {
            double p = pow(x, b[i]);
            b[i] -= min(0.00000001, delta * p * a[i] * L);
            a[i] -= delta * p;
        }
    }

    void main() {
        for (int i = 0; i < K; ++i) {
            a[i] = 1. * rand() / RAND_MAX;
            b[i] = 1. * rand() / RAND_MAX * 100;
        }
        for (int T = 0; T < 10000000; ++T) {
            double x = int(1. * rand() / RAND_MAX * 9999 + 1);
            double y_hat = eval(1 / (x + m)), y = GT(x);
            double delta = y_hat - y;
            update(delta, 1 / (x + m));
            if (T % 10000 == 0)
                print("x = {:4}, y_hat = {:.6f}, y = {:.6f}, delta: {:.6f}, f_6(10000) = {:.6f}\n", x, y_hat, y, delta, eval(1. / 10000));
            // for (int i = 0; i < 10; ++i) {
            //     print("{} {} ", a[i], b[i]);
            // }
            // print("\n");
        }
    }
}

namespace PE499 {
    const int n = 100000, m = 6, N = n + 10;

    double f[N];

    double eval(double t) {
        double y = -pow(t, 15), p = 1;
        for (; t; t = t * t) {
            p /= 2;
            y += p * t;
        }
        return y;
    }

    void main() {
        double L = 0, R = 1, m;
        // for (int i = 0; i < 100; ++i) {
        //     double v = 1. * i / 100;
        //     print("{} {}\n", v, eval(v));
        // }
        print("{}\n", eval(exp(-0.000001)));
        // for (; m = (L + R) / 2, L < R; ) {
        //     double f =
        // }
    }
}

int main() {
    PE499::main();
    return 0;
}