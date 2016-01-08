#include <cstdio>
#include <cmath>
using namespace std;

const int MOD = 1e9;
const int N = 1e7;

int S[N + 10];
long long _F[N + 10];
long long f(long long);
long long g(long long);
long long h(long long);
long long T(long long);

long long f(long long n) {
  if (n <= N)
    return _F[n];
  long long x = h(n), y = n - x;
  long long ret = f(x);
  for (long long t = 1; t * t <= y; ++t)
    ret += y - t * t + 1;

  return ret;
}

long long h(long long n) {
  long long lo = 1, hi = 2;
  for (; g(hi) <= n; hi = hi * 2)
    lo = hi;
  for (; lo != hi; ) {
    long long m = (lo + hi + 1) >> 1;
    if (g(m) <= n)
      lo = m;
    else
      hi = m - 1;
  }
  return lo;
}

long long g(long long n) {
  return n + f(n);
}

long long C2(long long v) {
  if (v % 2 == 0)
    return ((v / 2) % MOD) * ((v + 1) % MOD) % MOD;
  return ((v + 1) / 2 % MOD) * (v % MOD) % MOD;
}

long long T(long long n) {
  if (n == 1)
    return 1;
  long long x = h(n), y = n - x;
  long long ret = T(x);
  return (ret + C2(y)) % MOD;
}

int main() {
  S[1] = 1;
  for (int i = 1, idx = 0, cnt = 0; i <= N && idx <= N; ++i) {
    for (int t = 1; t * t <= S[i] && idx <= N; ++t)
      S[++idx] = ++cnt;
    S[++idx] = S[i];
  }
  for (int i = 1; i <= N; ++i)
    _F[i] = _F[i - 1] + sqrt(S[i]);
  for (int i = 1; i <= 100; ++i)
    if (_F[i] != f(i)) {
      printf("%d: %lld %lld\n", i, _F[i], f(i));
      break;
    }

  long long ans = 0;
  printf("%lld\n", T(1e18));
  printf("%lld\n", h(1e3));
  // for (int i = 1; i <= 1e3; ++i) {
  //   ans += S[i];
  // }
  printf("%lld\n", ans);
  return 0;
}
