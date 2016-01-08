#include <cstdio>
using namespace std;

bool is_prime(long long x) {
  for (long long i = 2; i * i <= x; ++i)
    if (x % i == 0)
      return false;
  return x != 1;
}

int main() {
  int ans = 0;
  for (int n = 1; n <= 1000; ++n) {
    int p = 3 * n * n + 3 * n + 1;
    if (p > 1e6)
      break;
    if (is_prime(p)) {
      printf("find a prime = %d\n", p);
      ans += 1;
    }
  }
  printf("%d\n", ans);
  return 0;
}
