#include <cstdio>
#include <algorithm>
using namespace std;

const int n = 1000, N = n + 10;

bool f[N][N][N];

void fill(int a, int b, int c) {
  if (a > b) swap(a, b);
  if (b > c) swap(b, c);
  if (a > b) swap(a, b);
  f[c][b][a] = true;
}

int main() {
  int t = 0, sum = 0;
  for (int i = 0; i <= n; ++i) {
    printf("%d\n", i);
    for (int j = 0; j <= i; ++j) {
      for (int k = 0; k <= j; ++k) {
        if (!f[i][j][k]) {
          for (int x = 1; x <= n - i; ++x)
            fill(i + x, j, k);
          for (int x = 1; x <= n - j; ++x)
            fill(i, j + x, k);
          for (int x = 1; x <= n - k; ++x)
            fill(i, j, k + x);
          for (int x = 1; x <= n - i && x <= n - j; ++x)
            fill(i + x, j + x, k);
          for (int x = 1; x <= n - j && x <= n - k; ++x)
            fill(i, j + x, k + x);
          for (int x = 1; x <= n - k && x <= n - i; ++x)
            fill(i + x, j, k + x);
          for (int x = 1; x <= n - i && x <= n - j && x <= n - k; ++x)
            fill(i + x, j + x, k + x);

          // printf("%d %d %d\n", i, j, k);
          sum += i + j + k;
        }
      }
    }
  }
  printf("%d\n", sum);
  return 0;
}
