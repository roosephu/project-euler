#include <cstdio>
using namespace std;

const int n = 20000, N = n + 10, SN = 220, MOD = 1e9;

long long f[N][SN];

int main() {
  f[1][1] = 3;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j * j <= i * 2; ++j) {
      for (int k = 1; k <= j + 1 && k <= n - i; ++k) {
        if (j == 1 || k == 1) {
          (f[i + k][k] += f[i][j] * 2) %= MOD;
        } else {
          (f[i + k][k] += f[i][j]) %= MOD;
        }
      }
    }
  }
  long long ans = 0;
  for (int i = 1; i * i <= n * 2; ++i) {
    printf("f[n][%d]: %lld\n", i, f[n][i]);
    ans += f[n][i];
  }
  printf("%lld\n", ans % MOD);
  return 0;
}
