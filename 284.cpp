#include <cstdio>
using namespace std;

const int mod = 14, n = 10000, N = n * 2 + 10;

int x[N];

int main() {
  x[0] = 49;
  long long ans = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= i * 2; ++j) {
      x[j + 1] += x[j] / mod;
      x[j] %= mod;
    }

    int sx = 0, sy = 2;
    for (int j = 0; j <= i; ++j) {
      sx += x[j];
      sy += mod - 1 - x[j];
    }
    if (x[i] != 0)
      ans += sx;
    if (x[i] != mod - 1)
      ans += sy;

    int t = x[i + 1]; // the new digit
    printf("%c", (t < 10 ? t + '0' : t + 'a' - 10));
    for (int j = 0; j <= i; ++j) {
      x[i + 1 + j] += 2 * t * x[j];
    }
    x[i * 2 + 2] += t * t;
  }
  printf("\nans = %lld\n", ans);
  return 0;
}
