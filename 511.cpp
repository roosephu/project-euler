#include <cstdio>
using namespace std;

const int M = 4321, MOD = 1e9;
const int pfac[4] = {5, 41, 25343, 237631};
const long long n = 1234567898765ll;

long long U[M], ans[M];

void convmul(long long *a, long long *b, long long *c) {
  long long t[M] = {0};
  for (int i = 0; i < M; ++i)
    for (int j = 0; j < M; ++j)
      (t[(i + j) % M] += a[i] * b[j]) %= MOD;
  for (int i = 0; i < M; ++i)
    c[i] = t[i];
}

int main() {
  ans[0] = 1;
  for (long long a = 1, i = 0; i < 2; a *= pfac[0], ++i)
    for (long long b = a, j = 0; j < 2; b *= pfac[1], ++j)
      for (long long c = b, k = 0; k < 2; c *= pfac[2], ++k)
        for (long long d = c, l = 0; l < 2; d *= pfac[3], ++l)
          U[d % M]++;
  // for (int i = 0; i < M; ++i)
  //   printf("%lld ", U[i]);
  // printf("\n");

  for (long long e = n; e; e >>= 1, convmul(U, U, U))
    e & 1 ? convmul(ans, U, ans), 0 : 0, printf("%lld\n", e);
  printf("%lld\n", ans[M - n % M]);

  return 0;
}
