#include <cstdio>
using namespace std;

const int n = 1e8, N = n + 10;

int dvs[N];

int gcd(int a, int b) {
  return a ? gcd(b % a, a) : b;
}

bool test(int x, int a, int b, int inv_a, int inv_b) {
  if (b % a == 0)
    return x % a == 0;
  if (a % b == 0)
    return x % b == 0;
  long q = (long)inv_b * x % a;
  long p = (long)inv_a * x % b;
  return a * p + b * q <= x;
}

bool can(int n, int m) {
  if (n % 2 == 1) {
    if (m % 2 == 1)
      return false;
    if (n == 1)
      return true;

    m /= 2;
    n /= 2;
    long k = m % n;
    return k * (n + 1) <= m;
  } else {
    n /= 2;
    return test(m, 2 * n - 1, 2 * n + 1, n, n) ||
      test(m - 1, 2 * n - 1, 2 * n + 1, n, n) ||
      test(m + 1, 2 * n - 1, 2 * n + 1, n, n);
  }
}

int main() {
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
      ++dvs[j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (dvs[i] < 399 || i % 2 == 1)
      continue;

    int cnt = 0;
    for (int x = 1; x * x <= i; ++x) {
      if (i % x == 0) {
        int y = i / x;
        if (!can(x, y) && !can(y, x)) {
          ++cnt;
        }
      }
    }
    if (cnt >= 200) {
      printf("ans for %d: %d\n", i, cnt);
      if (cnt == 200)
        break;
    }
  }

  return 0;
}
