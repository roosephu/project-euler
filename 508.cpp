#include "fmt/format.h"
#include "fmt/ostream.h"
#include <NTL/lzz_p.h>
#include <map>
#include <tuple>
using namespace fmt;
using namespace NTL;
using namespace std;

const long n = 1e15;
map<tuple<long, long, long, long>, zz_p> f;

zz_p dfs(long lx, long rx, long ly, long ry) {
    if (lx > rx || ly > ry)
        return zz_p(0);
    if (lx == 0 && rx == 0 && ly == 0 && ry == 0)
        return zz_p(0);
    if (!f.count({lx, rx, ly, ry})) {
        print("{} {} {} {}\n", lx, rx, ly, ry);
        zz_p ret{0};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                int e = (2 + (i + j) % 2) % 2;
                int x = (e - i + j) / 2, y = (e - i - j) / 2;
                int f = (2 + (x + y) % 2) % 2;
                int u = (f - x + y) / 2, v = (f - x - y) / 2;

                long y_max = v + ((rx - (8 - i + rx % 4) % 4) - i) / 2;
                long y_min = v - (i - (lx + (4 + i - lx % 4) % 4)) / 2;
                long x_max = u + (j - (ly + (4 + j - ly % 4) % 4)) / 2;
                long x_min = u - ((ry - (8 - j + ry % 4) % 4) - j) / 2;

                ret += zz_p(e + f) * ((y_max - y_min) / 2 + 1) * ((x_max - x_min) / 2 + 1);
            }
        }
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                int e = (2 + (i + j) % 2) % 2;
                int x = (e - i + j) / 2, y = (e - i - j) / 2;
                int f = (2 + (x + y) % 2) % 2;
                int u = (f - x + y) / 2, v = (f - x - y) / 2;

                long y_max = v + ((rx - (4 - i + rx % 2) % 2) - i) / 2;
                long y_min = v - (i - (lx + (2 + i - lx % 2) % 2)) / 2;
                long x_max = u + (j - (ly + (2 + j - ly % 2) % 2)) / 2;
                long x_min = u - ((ry - (4 - j + ry % 2) % 2) - j) / 2;

                ret += dfs(x_min, x_max, y_min, y_max);
                // print("({}, {}), ({}, {})\n", x_min, y_min, x_max, y_max);
            }
        }
        f[{lx, rx, ly, ry}] = ret;
    }
    return f[{lx, rx, ly, ry}];
}

int main() {
    zz_p::init(1000000007);

    // dfs(-9, 9, -9, 9);
    auto ans = dfs(-n, n, -n, n);
    print("ans = {}\n", ans);

    return 0;
}