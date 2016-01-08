#include <cstdio>
#include <cmath>
#include <set>
using namespace std;

const long long n = 1e12;

int gcd(int a, int b) {return a ? gcd(b % a, a) : b; }

long long ans = 0;

void test(long long m) {
  if (n < m)
    return ;
  long long sq = sqrt(m);
  if (sq * sq == m) {
    printf("find: %lld\n", m);
    ans += m;
  }
}

int main() {
  for (long long a = 1; a * a <= n; ++a)
    for (long long b = 1; a * a * b * b <= n && b < a; ++b) {
      if (gcd(a, b) != 1)
        continue;
      for (long long k = 1; k * k * a * a * b * b <= n; ++k) {
        test(k * a * a * k * b * b + k * a * b);
        test(k * a * a * k * a * b + k * b * b);
      }
    }
  printf("%lld\n", ans);
  return 0;
}
