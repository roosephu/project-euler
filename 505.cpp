#include "lib.h"

namespace PE505 {

    const long MOD = 1l << 60, MASK = MOD - 1, THRES = 1e12;
    const long N = 1 << 8;

    long f[N << 1];

    long reduce(long a, long b) {
        return ~max(a, b) & MASK;
    }

    long fy(long a, long b, long lv) {
        f[0] = a, f[1] = b;
        int n = 1 << lv;
        long *B = f + 2, *M = f + 1, *U = f;
        for (int i = 1; i < n; ++i) {
            *B = (3 * *M + 2 * *U) & MASK; ++B;
            *B = (2 * *M + 3 * *U) & MASK; ++B;
            ++M;
            if (i & 1) ++U;
        }
        for (int i = n - 1; i; --i) {
            f[i] = reduce(f[i << 1], f[i << 1 | 1]);
        }
        return f[1];
    }

    long clz(long x) {
        for (; x & (x - 1); )
            x &= x - 1;
        return x;
    }

    long cnt = 0;

    long dfs(long x0, long x1, long thres) {
        if ((thres & (thres - 1)) == 0 && thres <= N) { // fast evaluation
            int lv = 0;
            for (; (1l << lv) < thres; )
                ++lv;
            cnt += 1;
            if (cnt % 100000 == 0)
                print("{}/{}\n", cnt, THRES / N);
            return fy(x0, x1, lv);
        }
        // dfs
        long c = clz(thres);
        long thresL = 0, thresR = 0;
        if (thres < c + (c >> 1)) {
            thresL = thres - (c >> 1);
            thresR = c >> 1;
        } else {
            thresL = c;
            thresR = thres - c;
        }
        long L = dfs(x1, (3 * x1 + 2 * x0) & MASK, thresL);
        long R = dfs(x1, (3 * x0 + 2 * x1) & MASK, thresR);
        return reduce(L, R);
    }

    long dfs2(long n, long x0, long x1, long L, long R) {
        if (n >= THRES) return x1;
        if (L > R) return L - 1;
        cnt += 1;
        long Lv = dfs2(2 * n    , x1, (3 * x1 + 2 * x0) & MASK, MASK - R, MASK - L);
        long Rv = dfs2(2 * n + 1, x1, (2 * x1 + 3 * x0) & MASK, Lv + 1, MASK - L);
        return reduce(Lv, Rv);
    }

    void main() {
        // long ans = dfs(0, 1, THRES);
        long ans = dfs2(1, 0, 1, 0, MASK);
        print("cnt = {}, ans = {}\n", cnt, ans);
    }
}

int main() {
    PE505::main();
    return 0;
}
