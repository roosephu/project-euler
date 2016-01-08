#include <cstdio>
#include <set>
using namespace std;

const int N = 1e7, exp = 500500;
const int MOD = 500500507;

typedef long long int64;

int primes[N + 1];

int check(int k, int m) {
  long long ans = 1;
  int cnt = 0;
  for (int i = 1; i <= k; ++i) {
    int p = primes[i];
    long long cur_pow = p;
    while (cur_pow <= m) {
      ans = ans * cur_pow % MOD;
      ++cnt;
      cur_pow *= cur_pow;
    }
  }
  return cnt >= exp ? ans : -1;
}

int main() {
  for (int i = 2; i <= N; ++i) {
    if (!primes[i]) primes[++primes[0]] = i;
    for (int j = 1, k = N / i; primes[j] <= k; ++j) {
      int t = i * primes[j];
      primes[t] = 1;
      if (i % primes[j] == 0) break;
    }
  }

  int64 ans = 1;
  int L = 1, R = N, m;
  for (; m = (L + R) >> 1, L != R; ) {
    ans = check(primes[0], m);
    if (ans >= 0)
      R = m;
    else
      L = m + 1;
  }
  ans = check(primes[0], m);
  printf("%lld\n", ans);
  return 0;
}
