#include <cstdio>
#include <cstdlib>
using namespace std;

const int n = 100000, N = n + 10;

long long f[N][6];
int ans = 2000 - 1;

bool is_prime(long long x) {
  for (long long i = 2; i * i <= x; ++i)
    if (x % i == 0)
      return false;
  return x != 1;
}

void check(int cnt, long long v) {
  if (cnt == 3) {
    --ans;
    printf("find: %lld. left: %d\n", v, ans);
    if (ans == 0) {
      exit(0);
    }
  }
}


int main() {
  for (int i = 0; i < 6; ++i)
    f[0][i] = 1;
  long long cur = 2;

  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < 6; ++j) {
      f[i][j] = cur;
      cur += i;
    }
  }

  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < 6; ++j) {
      int cnt = 0;
      cnt += is_prime(f[i][j] - f[i - 1][j]);
      cnt += is_prime(f[i + 1][j] - f[i][j]);
      cnt += is_prime(f[i + 1][j] - 1 - f[i][j]);
      cnt += is_prime(f[i + 1][j] + 1 - f[i][j]);
      if (j == 0)
        cnt += is_prime(f[i + 2][0] - 1 - f[i][j]);
      // printf("%d: %d %d %d %d %d\n", f[i][j], f[i - 1][j], f[i + 1][j], f[i + 1][j] - 1, f[i + 1][j] + 1, f[i + 2][0] - 1);

      check(cnt, f[i][j]);
    }
    int cnt = 0;
    cnt += is_prime(f[i + 1][0] - 1 - f[i][0]);
    cnt += is_prime(f[i + 1][0] - f[i][0]);
    cnt += is_prime(f[i + 1][0] - 1 - f[i - 1][0]);
    cnt += is_prime(f[i + 2][0] - f[i + 1][0]);
    cnt += is_prime(f[i + 2][0] - 1 - f[i + 1][0]);
    check(cnt, f[i + 1][0] - 1);
  }

  return 0;
}
