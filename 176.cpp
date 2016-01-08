#include <cstdio>
using namespace std;

const int n = 100, N = n + 10;

int f[N];

int gcd(int a, int b) {
  return a ? gcd(b % a, a) : b;
}

int main() {
  for (int a = 1; a <= n; ++a)
    for (int b = 1; b < a && a * b <= n; ++b)
      if (gcd(a, b) == 1) {
        if ((a + b) % 2 == 0)
          f[a * b]++;
        if (2 * a * b <= n)
          f[2 * a * b]++;
      }
  for (int i = 1; i <= 20; ++i)
    printf("%d: %d\n", i, f[i]);
  for (int i = 1; i <= n; ++i)
    for (int j = 2; i * j <= n; ++j)
      f[i * j] += f[i];
  for (int i = 1; i <= n; ++i) {
    if (f[i] == 47547) {
      printf("ans = %d\n", i);
      break;
    }
  }
  return 0;
}
