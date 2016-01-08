#include <cstdio>
using namespace std;

const int mod = 84 * 2;

int gcd(int a, int b) {
  return a ? gcd(b % a, a) : b;
}

int main() {
  int ans = 0;
  for (int p = 1; p <= 1e4; ++p) {
    for (int q = 1; q < p; ++q) {
      if (gcd(p, q) != 1)
        continue;
      long long u = p * p - q * q;
      long long v = 2 * p * q;
      if (gcd(u, v) != 1)
        continue;

      long long a = u * u - v * v;
      long long b = 2 * u * v;
      long long c = u * u + v * v;
      if (c > 1e16)
        break;
      if (a < 0)
        a = -a;

      if ((a % mod) * (b % mod) % mod != 0) {
        ++ans;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
