#include <cstdio>
using namespace std;

long long fpm(long long b, long long e, long long m) {
  long long t = 1;
  for (; e; e >>= 1, b = b * b % m)
    e & 1 ? t = t * b % m : 0;
  return t;
}

long long C(long long n, long long m, long long p) {
  long long A = 1, B = 1;
  for (int i = 0; i < m; ++i) {
    A = A * (n - i) % p;
    B = B * (i + 1) % p;
  }
  return A * fpm(B, p - 2, p) % p;
}

bool is_prime(int x) {
  for (int i = 2; i * i <= x; ++i)
    if (x % i == 0)
      return false;
  return x != 1;
}

int main() {
  long long ans = 0, k = 1e3, a = 1e9, b = 1e5, complexity = 0;
  // printf("%lld\n", C(1, 0, 101));
  for (int p = a; p < a + b; ++p) {
    if (!is_prime(p))
      continue;
    printf("%d\n", p);
    complexity += p;
    // long long cur = 0;
    // int n = p - 1;
    // for (int i = 1; i <= n; ++i)
    //   cur += fpm(i, p - 2, p) * C(n - i + k - 1, n - i, p) % p;
    // ans += cur % p;
  }
  printf("ans = %lld, complexity = %lld\n", ans, complexity);
  return 0;
}
