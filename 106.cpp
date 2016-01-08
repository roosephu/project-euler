#include <cstdio>
#include <algorithm>
using namespace std;

const int n = 12;

int cb[20][20];

int main() {
  for (int i = 0; i < 20; ++i)
    for (int j = 0; j <= i; ++j)
      cb[i][j] = j ? cb[i - 1][j - 1] + cb[i - 1][j] : 1;

  int ans = 0;
  for (int x = 1; x + x <= n; ++x) {
    int t = cb[x + x][x] * (x - 1) / (x + 1) / 2;
    ans += cb[n][x + x] * t;
  }
  printf("%d\n", ans);

  return 0;
}
