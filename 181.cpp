#include <cstdio>
using namespace std;

const int n = 60, m = 40;

long long f[n + 10][m + 10];
long long cb[n + 10][m + 10];

int main() {
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= i; ++j)
      cb[i][j] = j ? cb[i - 1][j - 1] + cb[i - 1][j] : 1;
  f[0][0] = 1;
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= m; ++j) {
      if (i == 0 && j == 0)
        continue;
      printf("%d %d: %lld\n", i, j, f[i][j]);
      for (int p = n; p >= 0; --p)
        for (int q = m; q >= 0; --q)
          for (int k = 1; k * i + p <= n && k * j + q <= m; ++k)
            f[k * i + p][k * j + q] += f[p][q];
    }
  printf("%lld\n", f[n][m]);
  return 0;
}
