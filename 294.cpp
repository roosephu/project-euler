#include <cstdio>
#include <map>
using namespace std;

const long long n = 3138428376721ll, m = 23, M = m + 10;
const long long MOD = 1e9;

long long dp[M][M][M];
map<pair<long long, int>, long long> f;

long long fpm(long long b, long long e, long long m) {
  long long t = 1;
  for (; e; e >>= 1, b = b * b % m)
    e & 1 ? t = t * b % m : 0;
  return t;
}

long long solve(long long n, int m) {
  if (n == 1) return m < 10;
  if (n == 0) return m == 0;
  pair<long long, int> p = make_pair(n, m);
  if (!f.count(p)) {
    long long L = n / 2, R = n - L, ans = 0;
    for (int i = 0; i <= m; ++i)
      ans += solve(L, i) * solve(R, m - i) % MOD;
    f[p] = ans % MOD;
  }
  return f[p];
}

int main() {
  dp[0][0][0] = 1;

  long long s = 0, w = 1;
  for (int i = 0; i < m - 1; ++i) {
    long long cnt = (n + m - 2 - i) / (m - 1);
    s += cnt;
    for (int j = 0; j <= m; ++j) {
      for (int k = 0; k < m; ++k) {
        for (int t = 0; j + t <= m; ++t)
          (dp[i + 1][j + t][(k + w * t) % m] += dp[i][j][k] * solve(cnt, t)) %= MOD;
      }
    }

    w = w * 10 % m;
  }

  printf("%lld %lld\n", dp[m - 1][m][0], s);
  return 0;
}
