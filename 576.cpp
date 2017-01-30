#include "fmt/format.h"
#include <cmath>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
#include <NTL/ZZ.h>
using namespace fmt;
using namespace std;
using namespace NTL;

const double g = 0.00002;

// double dfs(double p, double L, double R, double one) {
//     if (L > R) return 0;
//     double np = (floor(one / p) + 1) * p - one;
//     double cnt = dfs(np, fmod(L, p), fmod(R, p), p);
//     return floor((cnt + L) / p) + 1;
// }

// double calc(double l, double g, double d) {
//     return l * dfs(l, d, g + d, 1);
// }

vector<pair<double, double>> dominate(double p, int bound) {
    vector<pair<double, double>> S;
    S.push_back({1, -1});
    for (int i = 0; i < bound; ++i) {
        double f = i * p;
        S.push_back({f - floor(f), f});
    }
    sort(S.begin(), S.end());

    pair<double, double> last = {-g, 0};
    deque<tuple<double, double, double>> Q;
    vector<pair<double, double>> ret;
    for (auto x : S) {
        // if (!Q.empty())
        //     print("{} {}: {} {}\n", x.first, x.second, Q.front().first + g, Q.front().first + g < x.first);
        while (!Q.empty() && get<1>(Q.front()) < x.first) {
            // if (get<1>(Q.front()) < x.first - 1e-7)
            //     print("break: [{}, {}]\n", get<1>(Q.front()), x.first);

            ret.push_back({get<0>(Q.front()), get<2>(Q.front()) - last.second});
            last = {0, get<2>(Q.front())};
            Q.pop_front();
        }
        while (!Q.empty() && get<2>(Q.back()) > x.second) {
            auto y = Q.back();
            Q.pop_back();
            if (get<0>(y) < x.first) {
                Q.push_back({get<0>(y), x.first, get<2>(y)});
                break;
            }
        }
        if (Q.empty()) {
            Q.push_back({x.first, x.first + g, x.second});
        } else {
            Q.push_back({get<1>(Q.back()), x.first + g, x.second});
        }
    }
    return ret;
}

int main() {
    vector<pair<double, double>> K;
    for (int i = 2; i <= 100; ++i) {
        if (ProbPrime(i)) {
            double sum = 0;
            double f = 1 / sqrt(i);
            auto intervals = dominate(f, 1000000);
            print("{}: {}\n", i, intervals.size());
            for (auto x : intervals) {
                sum += x.second;
                // print("{} {}\n", x.first, sum);
                K.push_back(x);
            }
        }
    }
    sort(K.begin(), K.end());
    double ans = -1e300, sum = 0;
    for (auto x : K) {
        sum += x.second;
        if (x.first >= g && sum >= ans) {
            ans = sum;
        }
    }
    print("ans = {:.8f}\n", ans);
    // for (auto x : intervals) {
    //     print("{} {}\n", x.first, x.second);
    // }
    // print("{:.6f}\n", calc(1 / sqrt(2), 0.06, 0.2427));
    return 0;
}