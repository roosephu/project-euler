#include <cstdio>
#include <cmath>
using namespace std;

const int n = 1e6, k = 2e4;
// const int n = 7, k = 3;

int main() {
  double ans = 1;

  for (int i = 0; i <= k / 2; ++i) {
    double p = 0;
    for (int j = 0; j < i; ++j)
      p += log((double)(k - 2 * j) * (k - 1 - 2 * j) / 2 / n / (j + 1));
    for (int j = 0; j < k - i; ++j)
      p += log(1 - (double)j / n);
    // printf("%.12f\n", (double)p);
    ans -= exp(p);
  }
  printf("%.12f\n", ans);
  return 0;
}
