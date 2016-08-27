#include "fmt/format.h"
#include <cmath>
#include <algorithm>
using namespace fmt;
using namespace std;

constexpr int n = 6, p2 = 3, State2 = 8, p3 = 2, State3 = 9;

long f[n + 1][2][n][State2][State3];

void decode(int S, int *v, int p, int base) {
    for (int i = 0; i < p; ++i) {
        v[i * 10 % p] += S % base;
        S /= base;
    }
}

int encode(int *v, int p, int base) {
    int ret = 0, pow = 1;
    for (int i = 0; i < p; ++i) {
        int t = min(base - 1, v[i] + (i == 0));
        ret += pow * t;
        pow *= base;
    }
    return ret;
}

int main() {
    f[0][0][0][1] = 1;
    for (int i = 0; i < n; ++i) {
        for (int b = 0; b < 2; ++b) {
            for (int m = 0; m < n; ++m) {
                for (int S2 = 0; S2 < State2; ++S2) {
                    for (int S3 = 0; S3 < State3; ++S3) {
                        if (f[i][b][m][S2][S3] == 0)
                            continue;
                        int v2[p2] = {0}, v3[p3] = {0};
                        decode(S2, v2, p2, 2);
                        decode(S3, v3, p3, 3);
                        print("i = {}, b = {}, m = {}, S = {}, v = [{}, {}]\n", i, b, m, S2, v[0], v[1]);
                        for (int x = 0; x <= 9; ++x) {
                            if (x != 0 || i != 0) {
                                int y = (m * 10 + x) % n;
                                int n_i = i + 1;
                                int n_S2 = encode(v2, p2, 2);
                                int n_S3 = encode(v3, p3, 3);
                                int n_m = y;
                                int n_b = b + v2[0];
                                // print("| i = {}, b = {}, m = {}, S = {}\n", n_i, n_b, n_m, n_S);
                                if (n_b <= 1) {
                                    f[n_i][n_b][n_m][n_S2][n_S3] += f[i][b][m][S2][S3];
                                }
                            }
                            rotate(v2, v2 + p2 - 1, v2 + p2);
                            rotate(v3, v3 + p3 - 1, v3 + p3);
                        }
                    }
                }
            }
        }
    }
    long ans = 0;
    for (int m = 0; m < n; ++m)
        for (int S = 0; S < State; ++S)
            ans += f[n][1][m][S];

    long ans2 = 0;
    for (int a = 2; a <= 2; ++a)
        for (int b = 0; b <= 9; ++b)
            for (int c = 0; c <= 9; ++c)
                for (int d = 0; d <= 9; ++d) {
                    int x = (a % n == 0) +
                            (b % n == 0) +
                            ((a * 10 + b) % n == 0) +
                            (c % n == 0) +
                            ((b * 10 + c) % n == 0) +
                            ((a * 100 + b * 10 + c) % n == 0) +
                            (d % n == 0) +
                            ((c * 10 + d) % n == 0) +
                            ((b * 100 + c * 10 + d) % n == 0) +
                            ((a * 1000 + b * 100 + c * 10 + d) % n == 0);
                    if (x == 1) {
                        ++ans2;
                        // print("{}\n", a * 1000 + b * 100 + c * 10 + d);
                    }
                }
    print("ans2 = {}\n", ans2);

    print("n = {}, f(n) = {}\n", n, ans);
    return 0;
}

/*
ans:
1: 9
2: 20
3: 360
4: 2701
5: 4096
6:
7: 161022
8:
9: 2136960
10: 0
11: 71101800
12:
13: 1057516028
14:
15:
16:
17: 195741994241
18:
19: 2253334981970
 */