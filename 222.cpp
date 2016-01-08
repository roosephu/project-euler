#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int n = 21, R = 50, rmin = 30, rmax = 50;

double f[n][1 << n];

int main() {
  // for (int i = 0, L = 30, R = 50; i < n; ++i) {
  //   if (0) {
  //     f[i] = L++;
  //   } else {
  //     f[i] = R--;
  //   }
  // }


  for (int i = 0; i < n; ++i)
    for (int S = 0; S < (1 << n); ++S)
      f[i][S] = 1e300;
  for (int S = 0; S < (1 << n); ++S) {
    for (int i = 0; i < n; ++i) {
      if (S == 0) {
        f[i][1 << i] = i + rmin;
        continue;
      }
      if ((S >> i & 1) == 1)
        continue;
      for (int x = 0; x < n; ++x) {
        if (S >> x & 1) {
          int T = S | (1 << i);
          f[i][T] = min(f[i][T], f[x][S] + 2 * sqrt(min(R * (i + x + 2 * rmin - R), 100000 + (i + rmin) * (x + rmin))));
        }
      }
    }
  }

  double ans = 1e300;
  for (int i = 0; i < n; ++i)
    ans = min(ans, f[i][(1 << n) - 1] + i + rmin);
  // double ans = f[0] + f[n - 1];

  // for (int i = 0; i < n - 1; ++i) {
  //   ans += sqrt(f[i] + f[i + 1] - R);
  // }
  printf("%.3f\n", ans * 1000);

  ans = 30 + 50;
  for (int i = 30; i < 50; ++i)
    ans += sqrt((i + i + 1 - R) * R) * 2;
  printf("%.3f\n", ans * 1000);
  return 0;
}
