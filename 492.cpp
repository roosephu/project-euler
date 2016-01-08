#include <cstdio>
using namespace std;

const int L = 1e9, R = L + 1e3;
const long long n = 1e15;

long long f(long long x, long long MOD) {
  return (x * x % MOD * 6 + 10 * x + 3) % MOD;
}

bool is_prime(int x) {
  for (int i = 2; i * i <= x; ++i)
    if (x % i == 0)
      return false;
  return x != 1;
}

long long solve(int MOD) {
  long long x = 1, y = 1, m = n - 1;
  for (int cnt = 0; m; ) {
    --m;
    x = f(x, MOD);
    y = f(y, MOD);
    y = f(y, MOD);
    ++cnt;

    if (x == y) {
      m %= cnt;
      printf("loop: %d\n", cnt);
    }
  }
  return x;
}

int main() {
  long long ans = 0;
  for (int MOD = L; MOD <= R; ++MOD)
    if (is_prime(MOD)) {
      printf("find prime: %d\n", MOD);
      ans += solve(MOD);
    }
  printf("%lld\n", ans);
  return 0;
}
