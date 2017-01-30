#include "fmt/format.h"
#include <algorithm>
#include <vector>
#include <map>
using namespace fmt;
using namespace std;

const long n = 1e12, m = 30;
const double eps = 1e-9;

long fib[m + 10];

double solve(long n, double LMT, double a, double b) {
    print("a = {}, b = {}, lmt = {}\n", a, b, LMT);
    double ret = 0;

    vector<double> values;
    map<double, long> dp;

    for (long v = 0; v * b <= LMT; ++v)
        for (long u = 0; u * a + v * b <= LMT; ++u)
            values.push_back(u * a + v * b);
    sort(values.begin(), values.end());

    dp[0] = 1;
    for (auto x : values) {
        long v = 1;
        if (x >= a)
            v += (--dp.upper_bound(x - a + eps))->second;
        if (x >= b)
            v += (--dp.upper_bound(x - b + eps))->second;
        dp[x] = v;

        if (v >= n) {
            ret = x;
            print("found: {}, size = {}\n", x, values.size());
            break;
        }
    }

    return ret;
}

int main() {
    fib[1] = fib[2] = 1;
    for (int i = 3; i <= m; ++i)
        fib[i] = fib[i - 1] + fib[i - 2];

    double ans = 0, lmt = 100;

    for (int i = 1; i <= m; ++i) {
        double cur = 0;
        for (bool first = true; cur == 0; first = false) {
            if (!first)
                lmt *= 2;
            cur = solve(n, lmt, sqrt(i), sqrt(fib[i]));
        }
        ans += cur;
    }
    print("ans = {:.8f}\n", ans);

    return 0;
}