#include "fmt/format.h"
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
using namespace fmt;

namespace PE177 {

    const double pi = acos(-1);
    const double eps = 1e-9;
    const int N = 200;

    double X[N], Y[N];

    struct node {
        int v[8];

        node(vector<int> h) {
            for (int i = 0; i < 8; ++i)
                v[i] = h[i];
        }
    };

    bool operator < (node a, node b) {
        for (int i = 0; i < 8; ++i)
            if (a.v[i] != b.v[i])
                return a.v[i] < b.v[i];
        return false;
    }

    void generate(double *values, int T) {
        for (int a = 1; a + T < 180; ++a) {
            int b = 180 - a - T;
            double v = sin(a * pi / 180) / sin(b * pi / 180);
            values[a] = v;
        }
    }

    node minimize(vector<int> h) {
        node ret(h);
        for (int c = 0; c < 2; ++c) {
            for (int i = 0; i < 8; ++i) {
                if (node(h) < ret)
                    ret = node(h);
                rotate(h.begin(), h.begin() + 2, h.end());
            }
            reverse(h.begin(), h.end());
        }
        return ret;
    }

    void main() {
        set<node> S;
        int ans = 0;
        for (int T = 1; T <= 90; ++T) {
            if (T % 10 == 0)
                print("{}\n", T);
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
                                node s = minimize(h);
                                if (S.count(s))
                                    continue;
                                // print("({}, {}, {}, {}, {}, {}, {}, {}): {}\n", s.v[0], s.v[1], s.v[2], s.v[3], s.v[4], s.v[5], s.v[6], s.v[7], v);
                                ans += 1;
                                S.insert(s);

                                // for (int j = 0; j < 2; ++j) {
                                //     for (int i = 0; i < 8; ++i) {
                                //         rotate(h.begin(), h.begin() + 1, h.end());
                                //         vector<int> x(h);
                                //         S.insert(x);
                                //     }
                                //     reverse(h.begin(), h.end());
                                // }
                            }
                        }
        }
        print("{}\n", ans);
        // for (auto h : S) {
        //     if (h[0] == 20 && h[1] == 50) {
        //         print("{}, {}, {}, {}, {}, {}, {}, {}\n", h[0], h[1], h[2], h[3], h[4], h[5], h[6], h[7]);
        //     }
        // }
    }
}

int main() {
    PE177::main();
    return 0;
}