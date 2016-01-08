#include <cstdio>
using namespace std;

long long f[30][30], ans, cb[30][30];

int main() {
  for (int i = 0; i <= 30; ++i)
    for (int j = 0; j <= i; ++j)
      cb[i][j] = j ? cb[i - 1][j - 1] + cb[i - 1][j] : 1;

  f[0][0] = 1;
  for (int i = 0; i < 9; ++i)
    for (int j = 0; j <= 18; ++j)
      for (int k = 0; k <= 3; ++k)
        f[i + 1][j + k] += f[i][j] * cb[j + k][k];
  for (int i = 1; i <= 9; ++i)
    for (int j = 1; j <= 3; ++j)
      ans += f[9][18 - j] * cb[17][j - 1];
  printf("%lld\n", ans);
  return 0;
}
