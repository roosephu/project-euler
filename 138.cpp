#include <cstdio>
#include <cmath>
using namespace std;

long long ans = 0, last = 1;

void check(long long a, long long b)  {
  if (b <= 0 || b >= a)
    return;
  long long u = a * a - b * b;
  long long v = 2 * a * b;
  if (u > v) {
    long long k = u;
    u = v;
    v = k;
  }

  if (u * 2 == v + 1 || u * 2 == v - 1) {
    long long cur = a * a + b * b;
    if (cur != last) {
      printf("find: %lld, ratio = %.6f\n", cur, 1. * cur / last);
      last = cur;
      ans += cur;
    }
  }
}

int main() {
  for (int a = 1; a <= 100000000; ++a) {
    int b = 2 * a / (sqrt(5) + 1);
    for (int i = -10; i <= 10; ++i)
      check(a, b + i);

    b = a / (sqrt(5) + 2);
    for (int i = -10; i <= 10; ++i)
      check(a, b + i);
  }
  printf("%lld\n", ans);
  return 0;
}
