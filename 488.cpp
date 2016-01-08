#include <cstdio>
#include <algorithm>
using namespace std;

const int n = 128, N = n + 10;

bool f[N][N][N];
int g[N][N];

bool get(int x, int y, int z) {
  if (x > y) swap(x, y);
  if (y > z) swap(y, z);
  if (x > y) swap(x, y);
  if (x == y || y == z) return false;
  return f[z][y][x];
}

bool guess(int x, int y, int z) {
  return ((x + 1) ^ (y + 1) ^ (z + 1)) == 0; // && ((x + 1) ^ (y + 1) ^ (z + 1)) % 2 == 0;
}

int main() {
  int ans = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < i; ++j)
      for (int k = 0; k < j; ++k) {
        bool b = false;
        for (int x = 1; x <= i; ++x)
          b |= get(i - x, j, k);
        for (int x = 1; x <= j; ++x)
          b |= get(i, j - x, k);
        for (int x = 1; x <= k; ++x)
          b |= get(i, j, k - x);

        f[i][j][k] = !b;

        if (!b) {
          if (k > 0)
            ans += i + j + k;
          g[i][j] = g[j][i] = k;
          g[j][k] = g[k][j] = i;
          g[k][i] = g[i][k] = j;
          // printf("%d %d %d\n", i, j, k);
        }
      }
  for (int i = 1; i < n; i += 2) {
    for (int j = 1; j < n; j += 2) {
      printf("%2d ", (g[i][j] + 1) / 2);
    }
    printf("\n");
  }

  for (int i = 1; i < n; ++i)
    for (int j = 1; j < i; ++j)
      for (int k = 1; k < j; ++k)
        if (f[i][j][k] != guess(i, j, k)) {
          printf("%d %d %d: %d\n", i, j, k, f[i][j][k]);
        }
  printf("%d\n", ans);
  return 0;
}
