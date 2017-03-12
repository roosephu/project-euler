#include "fmt/format.h"
#include "fmt/ostream.h"
#include <NTL/ZZ.h>
#include "bitset.h"
using namespace std;
using namespace fmt;
using namespace NTL;

namespace PE254 {
    const int MAX_LENGTH = 18, MAX_SUM = 150, MOD = 362880;

    unsigned int f[MAX_LENGTH + 1][MAX_SUM + 1][MOD / 32 + 100];
    long power[MAX_LENGTH + 2];

    long backtrace(int len, int sum, int m) {
        long ret = 0;
        for (; len; ) {
            for (int i = 0; i < 10 && i <= sum; ++i) {
                int pos = (m + (MOD - i) * power[len - 1]) % MOD;
                if (getbit(f[len - 1][sum - i], pos)) {
                    ret = ret * 10 + i;
                    len -= 1;
                    sum -= i;
                    m = pos;
                }
            }
        }
        return ret;
    }

    struct node {
        long x[10];

        node() {
            for (int i = 0; i < 10; ++i)
                x[i] = 0;
        }

        long sum() {
            long ret = 0;
            for (int i = 0; i < 10; ++i)
                ret += x[i];
            return ret;
        }
    };

    bool operator < (node a, node b) {
        long sa = a.sum(), sb = b.sum();
        if (sa != sb) return sa < sb;
        for (int i = 0; i < 10; ++i)
            if (a.x[i] != b.x[i])
                return a.x[i] > b.x[i];
        return false;
    }

    long calc(long s) {
        node ret; long y = 0;
        ret.x[9] = 1e18;
        for (int m = 0; m < MOD; ++m) {
            for (int i = 1; i <= MAX_LENGTH; ++i) {
                if (getbit(f[i][s], m)) {
                    // if (m == 5762)
                    long Y = backtrace(i, s, m), Y_old = Y;
                    node t;

                    t.x[9] += Y / MOD, Y %= MOD;
                    for (int fac = MOD, k = 8; k > 0; --k) {
                        fac /= k + 1;
                        t.x[k] += Y / fac;
                        Y %= fac;
                    }
                    // if (t.x[1] > 1) {
                    //     t.x[0] = t.x[1] - 1;
                    //     t.x[1] = 1;
                    // }

                    if (t < ret) {
                        ret = t;
                        y = Y_old;
                    }
                    break;
                }
            }
        }

        long sum = 0;
        for (int i = 0; i <= 9; ++i)
            sum += i * ret.x[i];
        print("Y = {}\n", y);
        return sum;
    }

    void main() {
        setbit(f[0][0], 0);

        power[0] = 1;
        for (int i = 0; i < 18; ++i)
            power[i + 1] = power[i] * 10 % MOD;

        for (int i = 0; i < MAX_LENGTH; ++i) {
            for (int s = 0; s <= MAX_SUM; ++s) {
                for (int m = 0; m < MOD; ++m) {
                    if (getbit(f[i][s], m)) {
                        for (int t = 0; t <= 9; ++t) {
                            if (s + t <= MAX_SUM) {
                                int pos = (m * 10 + t) % MOD;
                                setbit(f[i + 1][s + t], pos);
                            }
                        }
                    }
                }
            }
        }

        ZZ ans{0};
        for (int i = 1; i <= 150; ++i) {
            long cur = calc(i);
            print("{}: {}\n", i, cur);
            ans += cur;
        }
        print("ans = {}\n", ans);
    }
}

int main() {
    PE254::main();
    return 0;
}