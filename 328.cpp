#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

#define fst first
#define snd second

const int inf = 1e9;
const int n = 100, N = n + 10;

int f[N][N];
int log[N];

int main() {
  for (int i = 2; i <= n; ++i)
    log[i] = log[i / 2] + 1;
  for (int i = n; i; --i)
    for (int j = i + 1; j <= n; ++j) {
      f[i][j] = inf;
      for (int k = i; k <= j; ++k)
        f[i][j] = min(f[i][j], k + max(f[i][k - 1], f[k + 1][j]));
    }
  for (int i = 1; i <= 30; ++i) {
    for (int j = 1; i + j <= n; ++j) {
      printf("len = %d: start = %d, diff = %d\n", i, j, f[j][j + i] - j * (log[i + 1]));
    }
  }

  long ans = 0;
  for (int i = 1; i <= n; ++i)
    ans += f[1][i];
  printf("ans = %ld\n", ans);
  return 0;
}
