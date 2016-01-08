#include <cstdio>
#include <cmath>
using namespace std;

const long long LMT = 1e9;

long long gcd(long long a, long long b) {
  return a ? gcd(b % a, a) : b;
}

long long check(long long x, long long t) {
  if (x * 2 + t * 2 > LMT)
    return 0;
  if (2 * t + 1 == x || 2 * t - 1 == x) {
    printf("%lld %lld\n", x, t);
    return x * 2 + t * 2;
  }
  return 0;
}

int main() {
  long long ans = 0;
  for (long long a = 1; a * a <= LMT + 1; ++a) {
    long long lb = a / (sqrt(3) + 2) - 10, rb = a / (sqrt(3) + 2) + 10;
    for (long long b = lb; b <= rb && b < a; ++b) {
      if (b <= 0 || gcd(a, b) != 1)
        continue;
      ans += check(a * a + b * b, 2 * a * b);
    }
    for (long long lb = a / sqrt(3) - 10, rb = a / sqrt(3) + 10, b = lb; b <= rb && b < a; ++b) {
      if (b <= 0 || gcd(a, b) != 1)
        continue;
      ans += check(a * a + b * b, a * a - b * b);
    }
  }
  printf("%lld\n", ans);
  return 0;
}
