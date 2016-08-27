#include "fmt/format.h"
#include <NTL/ZZ.h>
#include <vector>
#include <cmath>
#include <tuple>
#include <set>
using namespace std;
using namespace fmt;
using namespace NTL;

const int LMT = 1e7, R_LMT = LMT / 10;

vector<pair<int, int>> G[R_LMT + 10];
set<tuple<long, long, long>> f;

int main() {
    for (int u = 1; u <= LMT; ++u)
        for (int v = 1; v < u && 2 * u * v <= LMT; ++v)
            if (GCD(u, v) == 1 && (u % 2 != v % 2)) {
                int a = u * u - v * v;
                int b = 2 * u * v;
                int c = u * u + v * v;

                for (int t = 1; a * t <= LMT && b * t <= LMT; ++t) {
                    if (a * t <= R_LMT)
                        G[a * t].push_back({b * t, c * t});
                    if (b * t <= R_LMT)
                        G[b * t].push_back({a * t, c * t});
                }
            }
    print("step 2..\n");

    long L2 = 0, L1 = 0;
    long ans = 0;

    int max_r = 0;
    for (int i = 1; i <= R_LMT; ++i) {
        long s = G[i].size();
        L2 += s * s;
        L1 += s;
        long r = i;
        for (int _i = 0; _i < G[i].size(); ++_i) {
            for (int _j = 0; _j < G[i].size(); ++_j) {
                auto &A = G[i][_i], &B = G[i][_j];
                long a = A.first, b = B.first;
                if (a * b - r * r > 0 && r * r * (a + b) % (a * b - r * r) == 0) {
                    auto c = r * r * (a + b) / (a * b - r * r);
                    long perimeter = 2 * (a + b + c);
                    if (perimeter <= LMT && a <= b && b <= c) {
                        tuple<long, long, long> s = {a, b, c};
                        if (f.count(s))
                            continue;
                        f.insert(s);

                        // print("a = {}, b = {}, c = {}, r = {}, IA = {:.3f}, IB = {:.3f}, IC = {:.3f}\n", a, b, c, r, sqrt(r * r + a * a), sqrt(r * r + b * b), sqrt(r * r + c * c));
                        ans += perimeter + sqrt(r * r + a * a) + sqrt(r * r + b * b) + sqrt(r * r + c * c) + 0.01;
                        if (i > max_r) {
                            max_r = i;
                        }
                    }
                }
            }
        }
    }
    print("L1 = {}, L2 = {}\n", L1, L2);
    print("ans = {}, #diff = {}, max_r = {}\n", ans, f.size(), max_r);
    return 0;
}