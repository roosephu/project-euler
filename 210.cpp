#include <cstdio>
#include <cmath>
using namespace std;

const long n = 1e9;

int main() {
  long c = n / 8, r = c * c * 2, ans = 0;
  for (long dx = -1.5 * c; dx <= 1.5 * c; ++dx) {
    long dy2 = r - dx * dx;
    if (dy2 > 0) {
      long dy = sqrt(dy2 - 1);
      while ((dy + 1) * (dy + 1) <= dy2 - 1)
        ++dy;
      while (dy * dy > dy2 - 1)
        --dy;
      ans += dy * 2 + 1;
    }
  }

  printf("init = %ld\n", ans);
  if (n % 4 != 0)
    while (true);
  ans += (n - n / 4) * (2 * n + 1);
  ans -= n - 1; // for the line x = y, O and C exclusive
  printf("ans = %ld\n", ans);
  return 0;
}
