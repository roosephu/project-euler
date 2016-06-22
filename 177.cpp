#include <cstdio>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const double pi = acos(-1);
const double eps = 1e-12;
const int N = 200;

double X[N], Y[N];

void generate(double *values, int T) {
    for (int a = 1; a + T < 180; ++a) {
        int b = 180 - a - T;
        double v = sin(a * pi / 180) / sin(b * pi / 180);
        values[a] = v;
    }
}

int main() {
    set<vector<int>> S;
    int ans = 0;
    for (int T = 1; T <= 90; ++T) {
        if (T % 10 == 0)
            printf("%d\n", T);
        generate(X, T);
        generate(Y, 180 - T);
        // if (T == 2) {
        //     printf("%.6f, %.6f\n", X[1], Y[1]);
        // }

        for (int a = 1; a + T < 180; ++a)
            for (int b = 1; b < T; ++b)
                for (int c = a; c + T < 180; ++c)
                    for (int d = 1; d < T; ++d) {
                        double v = X[a] * Y[b] * X[c] * Y[d];
                        if (-eps <= v - 1 && v - 1 <= eps) {
                            vector<int> h = {a, 180 - T - a, b, T - b, c, 180 - T - c, d, T - d};
                            if (S.count(h))
                                continue;
                            // printf("(%d, %d, %d, %d, %d, %d, %d, %d): %.6f\n", a, 180 - T - a, b, T - b, c, 180 - T - c, d, T - d, v);
                            ans += 1;

                            for (int j = 0; j < 2; ++j) {
                                for (int i = 0; i < 8; ++i) {
                                    rotate(h.begin(), h.begin() + 1, h.end());
                                    vector<int> x(h);
                                    S.insert(x);
                                }
                                reverse(h.begin(), h.end());
                            }
                        }
                    }
    }
    printf("%d\n", ans);
    for (auto h : S) {
        if (h[0] == 20 && h[1] == 50) {
            printf("%d, %d, %d, %d, %d, %d, %d, %d\n", h[0], h[1], h[2], h[3], h[4], h[5], h[6], h[7]);
        }
    }
    return 0;
}
