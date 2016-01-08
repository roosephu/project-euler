#include <cstdio>
using namespace std;

const int MOD = 987654321;

long long P(long long n) {
  if (n == 1)
    return 1;
  if (n == 2 || n == 3)
    return 2;
  long long x = n / 4;
  long long ret = P(x) * 4;
  if (n % 4 < 2)
    ret -= 2;
  return ret;
}

long long S(long long n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  if (n == 2)
    return 3;
  if (n == 3)
    return 5;
  long long x = n / 4;
  long long ret = S(x - 1) * 16 % MOD - (x - 1) * 4 % MOD + 5;
  for (long long y = x * 4; y <= n; ++y)
    ret += P(y) % MOD;
  return (ret + MOD) % MOD;
}

int main() {
  printf("%lld %lld %lld %lld\n", P(1), P(9), P(1000), S(1e18));
  return 0;
}
