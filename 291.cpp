#include <cstdio>
using namespace std;

bool is_prime(long long p) {
  // return true;
  for (long long i = 2; i * i <= p; ++i)
    if (p % i == 0)
      return false;
  return p != 1;
}

int main() {
  long long ans = 0;
  for (int x = 1; x <= 5e7; ++x) {
    if (x % 100000 == 0)
      printf("%d\n", x);
    long long p = 1ll * x * x + 1ll * (x + 1) * (x + 1);
    if (is_prime(p)) {
      // printf("find p = %lld\n", p);
      ans += p;
    }
  }
  printf("%lld\n", ans);
  return 0;
}
