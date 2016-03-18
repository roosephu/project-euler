#include <cstdio>
#include <algorithm>
using namespace std;

const int n = 20000, N = n + 10;

double f[N], g[N];

int main() {
  for (int i = 1; i <= n; ++i) {
    if (i % 100 == 0)
      printf("%d\n", i);
    f[i] = g[i] = i;
    if (i >= 2) {
      int start = i / 2 + 1;
      double s = 1, cur = 1;
      for (int t = start; t <= i; ++t) {
        cur = cur * (i - t) / t;
        s += cur;
      }
      double scale = (i - g[start - 1]) / s;
      for (int t = start; t < i; ++t) {
        g[t] = g[t - 1] + scale;
        scale = scale * (i - t) / t;
      }
    }

    for (int t = 0; t <= 8; ++t) {
      for (int j = i - 1; j >= 1; --j) {
        double v = (g[j - 1] * (i - j) + g[j + 1] * j) / i;
        g[j] = max(g[j], v);
        f[j] = v;
      }
    }
    // for (int j = 1; j <= i; ++j) {
    //   printf("%.6f ", f[j]);
    // }
    // printf("\n");
  }
  // for (int j = 1; j <= n; ++j)
  //   printf("%.6f ", g[j]);
  printf("%.6f\n", f[n / 2]);
  return 0;
}
