#include <cstdio>
using namespace std;

const int n = 43, m = 47, M = 100;

int o[M][M];

int main() {
  long long ans = 1ll * (n + 2) * n * (n + 1) / 6 * m * (m + 1) * (m + 2) / 6;

  for (int i = 0; i <= n * 2; ++i)
    for (int j = 0; j <= m * 2; ++j)
      if ((i + j) % 2 == 0) {
        int x = (i + j) / 2;
        int y = (i + M - j) / 2;
        o[x + 1][y + 1] = 1;
      }
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < M; ++j)
      printf("%d", o[i][j]);
    printf("\n");
  }

  for (int i = 1; i < M; ++i)
    for (int j = 1; j < M; ++j)
      o[i][j] += o[i - 1][j] + o[i][j - 1] - o[i - 1][j - 1];
  for (int lx = 1; lx < M; ++lx)
    for (int rx = lx + 1; rx < M; ++rx)
      for (int ly = 1; ly < M; ++ly)
        for (int ry = ly + 1; ry < M; ++ry) {
          int s = o[rx][ry] - o[rx][ly - 1] - o[lx - 1][ry] + o[lx - 1][ly - 1];
          if (s == (rx - lx + 1) * (ry - ly + 1)) {
            int mi = (rx + ry - M / 2 - 1) / 2;
            int mj = (rx - ly + M / 2 + 1) / 2;
            // printf("%d %d\n", mi, mj);
            ans += (n - mi + 1) * (m - mj + 1);
          }
        }
  printf("%lld\n", ans);
  return 0;
}
