#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

const double max_peri = 100000;
const int R = 100000 / 3 + 100;
const int LB = 36e7, RB = 38e7;

map<int, vector<pair<int, int>>> vec;

int main() {
    printf("final answer = %.6f\n", 21891.21456925 + 63578.07405778 + 47443.54616685 + 80164.02119302 + 126834.3457490 + 31077.02446861 + 40462.41033161 + 43252.11959952 + 124724.37939820 + 308005.22074455 + 458916.82537900 + 718525.09316016 + 137209.60553094 + 155926.14357440 + 265927.55081785 + 192479.53078193);
    for (int i = -R; i <= R; ++i) {
        // if (i % 1000 == 0)
        //     printf("%d\n", i);
        int bound = sqrt(R * R - i * i) + 10;
        for (int j = -bound; j <= bound; ++j) {
            int x = i * i + j * j;
            if (LB <= x && x < RB) {
                vec[x].push_back({i, j});
            }
        }
    }
    long f2 = 0, f1 = 0;

    double ans = 0;
    for (auto v : vec) {
        long s = v.second.size();
        f1 += s;
        f2 += s * s;
        for (auto a : v.second) {
            // printf("points: (%d, %d)\n", a.first, a.second);
        }

        for (auto a : v.second) {
            for (auto b : v.second) {
                if (a >= b)
                    continue;
                int x = 5 - a.first - b.first;
                int y = -a.second - b.second;
                if (x * x + y * y == v.first) {
                    if (make_pair(x, y) != a && make_pair(x, y) != b) {
                        double peri = 0;
                        peri += hypot(a.first - b.first, a.second - b.second);
                        peri += hypot(a.first - x, a.second - y);
                        peri += hypot(b.first - x, b.second - y);
                        if (peri <= max_peri) {
                            ans += peri;
                            printf("(%d, %d), (%d, %d), (%d, %d): %.4f\n", a.first, a.second, b.first, b.second, x, y, peri);
                        }
                    } else {
                        // printf("xxx (%d, %d), (%d, %d), (%d, %d)\n", a.first, a.second, b.first, b.second, x, y);
                    }
                }
            }
        }
    }
    printf("f1 = %ld, f2 = %ld\n", f1, f2);
    printf("ans = %.8f\n", ans / 3);
    printf("LB = %d, RB = %d\n", LB, RB);
    return 0;
}

/*
  [1, 1e5): 21891.21456925
  [1e5, 1e6): 63578.07405778
  [1e6, 3e6): 47443.54616685
  [3e6, 5e6): 80164.02119302
  [5e6, 8e6): 126834.34574903
  [8e6, 10e6): 31077.02446861
  [10e6, 14e6): 0
  [14e6, 16e6): 40462.41033161
  [16e6, 18e6): 43252.11959952
  [18e6, 20e6): 0
  [20e6, 25e6): 124724.37939820
  [25e6, 45e6): 308005.22074455
  [45e6, 65e6): 458916.82537900
  [65e6, 1e8): 718525.09316016
  [10e7, 12e7): 0
  [12e7, 14e7): 0
  [14e7, 16e7): 0
  [16e7, 18e7): 137209.60553094
  [18e7, 20e7): 0
  [20e7, 22e7): 0
  [22e7, 24e7): 155926.14357440
  [24e7, 26e7): 0
  [26e7, 28e7): 0
  [28e7, 30e7): 265927.55081785
  [30e7, 32e7): 0
  [32e7, 34e7): 0
  [34e7, 36e7): 192479.53078193
  [36e7, 38e7): 0
 */
