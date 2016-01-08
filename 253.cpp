#include <cstdio>
#include <algorithm>
using namespace std;

const int n = 200, N = n + 3;

double f[N][N][N][2][2];

int main() {
  f[1][1][1][0][1] = f[1][1][1][0][0] = f[1][1][1][1][0] = 1;
  for (int i = 1; i < n; ++i)
    for (int j = 1; j <= n; ++j)
        for (int k = 0; k <= n; ++k)
          for (int p = 0; p < 2; ++p)
            for (int q = 0; q < 2; ++q) {
              if (f[i][j][k][p][q] == 0)
                continue;
              if (k == 1 && p == 1 && q == 1)
                continue;
              int nk = k - 1;
              if (p == 0) {
                if (k > 0) {
                  f[i + 1][j][k    ][1][q] += f[i][j][k][p][q];
                  f[i + 1][j][k    ][0][q] += f[i][j][k][p][q];
                }
                f[i + 1][max(j, k + 1)][k + 1][1][q] += f[i][j][k][p][q];
                f[i + 1][max(j, k + 1)][k + 1][0][q] += f[i][j][k][p][q];
              }
              if (q == 0) {
                if (k > 0) {
                  f[i + 1][j][k    ][p][1] += f[i][j][k][p][q];
                  f[i + 1][j][k    ][p][0] += f[i][j][k][p][q];
                }
                f[i + 1][max(j, k + 1)][k + 1][p][1] += f[i][j][k][p][q];
                f[i + 1][max(j, k + 1)][k + 1][p][0] += f[i][j][k][p][q];
              }
              if (i == 0)
                nk = 1;
              // printf("%d %d %d %d: %f, nk = %d\n", i, k, p, q, f[i][k][p][q], nk);

              if (k > 1)
                f[i + 1][j][k - 1][p][q] += nk * f[i][j][k][p][q];
              if (k > 0)
                f[i + 1][j][k    ][p][q] += nk * 2 * f[i][j][k][p][q];
              f[i + 1][max(j, k + 1)][k + 1][p][q] += nk * f[i][j][k][p][q];
            }

  double num = 0, den = 0;
  for (int j = 1; j <= n; ++j) {
    double v = f[n][j][1][1][1];
    if (!v) break;
    num += j * v;
    den += v;
    // printf("%d: %f\n", j, v);
  }
  printf("ans = %.6f\n", num / den);
  return 0;
}
