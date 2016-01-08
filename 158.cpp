#include <cstdio>
#include <algorithm>
using namespace std;

long long cb[40][40], p[40];

int main() {
  for (int i = 0; i < 30; ++i)
    for (int j = 0; j <= i; ++j)
      cb[i][j] = j ? cb[i - 1][j - 1] + cb[i - 1][j] : 1;
  for (int x = 0; x < 26; ++x)
    for (int y = x + 1; y < 26; ++y)
      for (int l1 = 0; l1 <= 25 - y; ++l1)
        for (int l2 = 0; l2 <= y - x - 1; ++l2)
          for (int l3 = 0; l3 <= y - x - 1 - l2; ++l3)
            for (int l4 = 0; l4 <= x; ++l4)
              p[l1 + l2 + l3 + l4 + 2] += cb[25 - y][l1] * cb[y - x - 1][l2] * cb[y - x - 1 - l2][l3] * cb[x][l4];
  long long ans = 0;
  for (int i = 1; i <= 26; ++i) {
    printf("%lld\n", p[i]);
    ans = max(ans, p[i]);
  }
  printf("%lld\n", ans);
  return 0;
}
