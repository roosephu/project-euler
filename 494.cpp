#include "lib.h"
#include "NTL/RR.h"


namespace PE494 {
    const long MAX_THRES = 1.31e7;
    const int n = 90, maxN = n + 10;
    const double M_LN3 = log(3);

    long xs[maxN], ys[maxN], rank[maxN], idx[maxN];
    double coef[maxN];
    set<vector<int>> S;
    set<long> T;
    unsigned int is_suf[MAX_THRES / 32 + 10];

    long step(long x) {
        return x & 1 ? x * 3 + 1 : x / 2;
    }

    bool is_inf_form(int n) {
        copy(xs, xs + n, ys);
        sort(ys, ys + n);
        for (int i = 0; i < n; ++i) {
            rank[i] = lower_bound(ys, ys + n, xs[i]) - ys;
            idx[rank[i]] = i;
        }
        coef[0] = 0;
        for (int i = 0; i < n - 1; ++i) {
            if (xs[i] & 1){
                coef[i + 1] = coef[i] + M_LN3;
            } else {
                coef[i + 1] = coef[i] - M_LN2;
            }
        }
        for (int i = 0; i < n - 1; ++i) {
            if (coef[idx[i + 1]] < coef[idx[i]]) {
                return false;
            }
        }
        return true;
    }

    void main1() {

        int cnt = 0;

        for (int i = 1; i <= MAX_THRES; ++i) {
            if (i % 1000000 == 0) print("#{}: cnt = {}\n", i, cnt);
            long x = i;

            int length = -1;

            for (int t = 0; t <= n; ++t) {
                xs[t] = x;
                if ((x & (x - 1)) == 0) {
                    length = t;
                    break;
                }
                x = step(x);
                assert(x <= 1e18);
            }
            if (length >= 1) {
                if (!is_inf_form(length)) {
                    // for (int j = 0; j <= length; ++j) {
                    //     print("{} ", xs[j]);
                    // }
                    // print("\n");

                    setbit(is_suf, i);
                    ++cnt;
                }
            }
        }
        for (int i = 1; i <= MAX_THRES; ++i) {
            if (!getbit(is_suf, i)) continue;
            long x = i, t = 0;
            bool clear = false;
            for (; x & (x - 1); ) {
                t += 1;
                x = step(x);
                if (x <= MAX_THRES && getbit(is_suf, x)) {
                    clear = true;
                    break;
                }
            }
            if (!clear) {
                print("{} with {} steps\n", i, t);
                T.insert(i);
            }
        }


        print("cnt = {}, |T| = {}\n", cnt, T.size());
    }

    long dfs(ZZ x, int d) {
        if (d == 0) {
            return 1;
        }
        int ret = 0;
        if (x % 2 == 0 && x % 3 == 1) {
            ret = dfs((x - 1) / 3, d - 1);
        }
        ret += dfs(x * 2, d - 1);
        return ret;
    }

    void main() {
        int starts[] = {9, 19, 37, 51, 155, 159};
        int steps[] = {15, 16, 17, 20, 81, 50};

        long ans = 0;
        for (int i = 0; i < 6; ++i) {
            if (steps[i] <= n) {
                long delta = dfs(ZZ(starts[i]), n - steps[i]);
                ans += delta;
                print("start = {}, delta = {}\n", starts[i], delta);
            }
        }
        print("ans = {}\n", ans); // real answer = ans + fib(90)
    }
}

int main() {
    PE494::main();
    return 0;
}
