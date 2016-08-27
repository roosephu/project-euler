#include <algorithm>
#include <NTL/LLL.h>
#include <NTL/ZZ.h>
#include "fmt/format.h"
using namespace NTL;
using namespace fmt;

const int MOD = 1e7;

struct vector {
    long a, b, c;
};

int t0 = 0, t1 = 0, t2 = 1;

long R() {
    int t3 = (t0 + t1 + t2) % MOD;
    t0 = t1;
    t1 = t2;
    t2 = t3;
    return t0;
}

Vec<ZZ> next_vec() {
    Vec<ZZ> ret;
    ret.append(ZZ(R() - R()));
    ret.append(ZZ(R() + R()));
    ret.append(ZZ(R() * R()));
    return ret;
}

ZZ norm(Vec<ZZ> x) {
    ZZ ret(0);
    for (int i = 0; i < x.length(); ++i) {
        ZZ &t = x[i];
        if (t > 0)
            ret += t;
        else
            ret -= t;
    }
    return ret;
}

int main() {
    long ans = 0;
    for (int t = 1; t <= (long) 2e7; ++t) {
        if (t % 100000 == 0) {
            print("t = {}\n", t);
        }
        Mat<ZZ> M;
        M.SetDims(2, 3);
        ZZ det2;
        M[0] = next_vec();
        M[1] = next_vec();

        LLL(det2, M, 0);

        Vec<ZZ> a = M[0], b = M[1];
        ZZ z_cur(-1);
        for (int i = -1; i <= 1; ++i)
            for (int j = -1; j <= 1; ++j)
                if (i || j) {
                    ZZ now = norm(a * i + b * j);
                    if (z_cur < 0 || z_cur > now)
                        z_cur = now;
                }
        // z_cur = max(norm(a), norm(b));
        long cur = trunc_long(z_cur, 64);
        ans += cur;
        // cout << "cur: " << z_cur << endl
        //      << "M: " << M[0] << ", " << M[1] << endl;
    }
    print("ans = {}\n", ans);

    return 0;
}
