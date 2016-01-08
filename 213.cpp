#include <cstdio>
#include <cstring>
using namespace std;

const int n = 30, m = 50, N = n + 10;

double f[N][N], g[N][N], T[N][N];

int main() {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      T[i][j] = 1;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      for (int x = 0; x < n; ++x)
        for (int y = 0; y < n; ++y)
          f[x][y] = i == x && j == y;
      for (int t = 0; t < m; ++t) {
        memset(g, 0, sizeof(g));
        for (int x = 0; x < n; ++x)
          for (int y = 0; y < n; ++y) {
            double p = f[x][y] / ((x != 0) + (y != 0) + (x != n - 1) + (y != n - 1));
            if (x != 0) g[x - 1][y] += p;
            if (y != 0) g[x][y - 1] += p;
            if (x != n - 1) g[x + 1][y] += p;
            if (y != n - 1) g[x][y + 1] += p;
          }

        for (int x = 0; x < n; ++x)
          for (int y = 0; y < n; ++y)
            f[x][y] = g[x][y];
      }
      for (int x = 0; x < n; ++x)
        for (int y = 0; y < n; ++y)
          T[x][y] *= 1 - f[x][y];
    }

  double ans = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      ans += T[i][j];
  printf("%.7f\n", ans);
  return 0;
}
