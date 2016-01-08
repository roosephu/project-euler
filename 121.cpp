#include <cstdio>
using namespace std;

const int n = 15, N = n + 10;

double f[N][N];

int main() {
  f[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= i; ++j) {
      f[i][j] = f[i - 1][j] * i / (i + 1) + f[i - 1][j - 1] / (i + 1);
    }
  }

  double s = 0;
  for (int i = n / 2 + 1; i <= n; ++i)
    s += f[n][i];
  printf("%d %.6lf\n", (int)(1 / s), s);
  return 0;
}
