#include <cstdio>
#include <cstring>
using namespace std;

const int n1 = 5678027, n2 = 7208785, N = n2 + 100;

bool b[5][N], o[5][N], P[N * 5];

bool is_prime(int x) {
  for (int i = 2; i * i <= x; ++i)
    if (x % i == 0)
      return false;
  return x != 1;
}

long long solve(int n) {
  memset(b, 0, sizeof(b));
  memset(o, 0, sizeof(o));
  memset(P, 0, sizeof(P));

  long long start = (n - 2ll) * (n - 3ll) / 2 + 1;
  for (long long p = 2; p * p <= start + n * 5; ++p)
    if (is_prime(p))
      for (long long i = (start - 1) / p + 1; i * p < start + n * 5; ++i)
        P[i * p - start] = true;

  int idx = 0;
  for (int i = -2; i <= 2; ++i) {
    int m = n + i;
    long long val = m * (m - 1ll) / 2 + 1;
    for (int j = 0; j < m; ++j) {
      b[i + 2][j] = !P[idx];
      ++idx;
    }
  }
  for (int i = -1; i <= 1; ++i) {
    int m = n + i;
    for (int j = 0; j < m; ++j) {
      if (!b[i + 2][j])
        continue;
      int cnt = 0;
      for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy)
          if (dy + j >= 0)
            cnt += b[i + 2 + dx][j + dy];
      if (cnt >= 3)
        for (int dx = -1; dx <= 1; ++dx)
          for (int dy = -1; dy <= 1; ++dy)
            if (dx + j >= 0)
              o[i + 2 + dx][j + dy] = b[i + 2 + dx][j + dy];
    }
  }

  long long ret = 0;
  start = n * (n - 1ll) / 2 + 1;
  for (int i = 0; i < n; ++i)
    ret += o[0 + 2][i] * (i + start);
  printf("S(%d) = %lld\n", n, ret);
  return ret;
}

int main() {
  printf("%lld\n", solve(n1) + solve(n2));
  return 0;
}
