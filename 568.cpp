#include "fmt/format.h"
#include "fmt/ostream.h"
#include <NTL/RR.h>
#include <cmath>
using namespace std;
using namespace fmt;
using namespace NTL;

const double eps = 1e-20;
const long n = 123456789l;

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

int main() {
    double ans = log(H(n)) - n * log(2);
    ans -= log(10) * floor(ans / log(10));
    print("{:.8f}\n", exp(ans));

    return 0;
}