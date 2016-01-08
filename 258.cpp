#include <cstdio>
using namespace std;

const int MOD = 20092010, N = 2000;
const long long n = 1e18;

long long t[N], b[N];

void polymul(long long *x, long long *y, long long *z) {
  long long t[N * 2] = {0};

  // t = x * y
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      t[i + j] += x[i] * y[j] % MOD;

  // t = t % (x^N - x - 1)
  for (int i = N * 2 - 1; i >= N; --i) {
    t[i - N    ] += t[i];
    t[i - N + 1] += t[i];
  }

  // z = t
  for (int i = 0; i < N; ++i)
    z[i] = t[i] % MOD;
}

int main() {
  b[1] = 1;
  t[0] = 1;
  for (long long e = n; e; e >>= 1, polymul(b, b, b))
    e & 1 ? polymul(t, b, t), 0 : 0;

  long long ans = 0;
  for (int i = 0; i < N; ++i)
    ans += t[i];

  printf("%lld\n", ans % MOD);

  return 0;
}
