#include <cstdio>
using namespace std;

const int n = 100, k = 25, t = 22;

double cb[n][n];

int main() {
  double ans = 0, deno = 1;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j <= i; ++j)
      cb[i][j] = j ? cb[i - 1][j - 1] + cb[i - 1][j] : 1;
  ans = cb[k][t];
  for (int i = 0; i < k - t; ++i)
    ans /= n - i;

  double f = 0;
  for (int i = 0; i <= t; ++i) {
    f += (i & 1 ? -1 : 1) * cb[t][i] * deno;
    deno /= n - (k - t) - i;
  }
  printf("%.12f\n", ans * f);
  return 0;
}
