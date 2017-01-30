#include "fmt/format.h"
using namespace fmt;

const int n = 7, N = 10;

long A[N][N], a[N];
long cnt = 0, total = 0;
long ans = 0;

template<class T> T test(T t) {
    T ret = 0;
    for (int i = 0; i <= n; ++i) {
        ret = ret * (t + i - n) + a[i];
    }
    return ret;
}

long abs(long x) {
    return x > 0 ? x : -x;
}

void dfs(int t) {
    if (t > n) {
        total += 1;
        for (int i = 1; i <= n; ++i)
            if (test(i) * test(i + 0.9999) > 0)
                return;

        cnt += 1;
        // for (int i = 1; i <= n; ++i)
        //     print("{}, ", a[i]);
        // print("\n");
        ans += abs((long) (test(-1))) - 1;
        return;
    }

    long lo = -1e18, hi = 1e18;
    for (int x = 1; x <= t + 1; ++x) {
        long s = 0;
        for (int i = 0; i < t; ++i)
            s -= a[i] * A[n - i][n - t] * A[x][t - i];
        s /= A[n - t][n - t];

        if (s > lo && (x % 2 != t % 2))
            lo = s;
        if (s < hi && (x % 2 == t % 2))
            hi = s;
    }
    if (t <= 3)
        print("t = {}, lo = {}, hi = {}\n", t, lo, hi);

    for (int i = lo; i <= hi; ++i) {
        a[t] = i;
        dfs(t + 1);
    }
}

int main() {
    for (int i = 0; i <= n + 1; ++i)
        for (int j = 0; j <= i; ++j)
            A[i][j] = j ? A[i - 1][j - 1] * i : 1;

    a[0] = 1;
    dfs(1);
    print("total/cnt = {}/{}, ans = {}\n", total, cnt, ans);
    return 0;
}