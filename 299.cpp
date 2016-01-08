#include <cstdio>
using namespace std;

const int LMT = 1e8, n = LMT / 3, N = n + 100;

int primes[N], lnk[N];
int top, val[100], cnt[100];
int ans;

void dfs(int dep, long long a, long long b) {
  if (dep == 0) {
    long long d = a * a / 2 / b;
    if (b + d + 2 * a < LMT) {
      ++ans;
      // printf("%lld %lld %lld\n", a, b + a, d + a);
    }
    if (b <= d) {
      long long true_b = a + b + d;
      if (true_b * 2 < LMT)
        ++ans;
    }
    return ;
  }

  for (int i = 0; i <= cnt[dep]; ++i) {
    dfs(dep - 1, a, b);
    b *= val[dep];
  }
}

int main() {
  for (int i = 2; i <= n; ++i) {
    if (!primes[i]) primes[++primes[0]] = i, lnk[i] = i;
    for (int j = 1, k = n / i; primes[j] <= k; ++j) {
      int t = i * primes[j]; primes[t] = 1, lnk[t] = primes[j];
      if (i % primes[j] == 0) break;
    }
  }

  for (int a = 2; a <= n; a += 2) {
    if (a % 100000 == 0)
      printf("progress: %d\n", a);
    top = 0;
    for (int x = a; x != 1; ) {
      int p = lnk[x];
      ++top;
      val[top] = p, cnt[top] = 0;
      for (; lnk[x] == p; )
        x /= p, cnt[top] += 2;
    }
    for (int i = 1; i <= top; ++i)
      if (val[i] == 2)
        --cnt[i];

    dfs(top, a, 1);
  }
  printf("%d\n", ans);
  return 0;

  ans = 0;
  for (int a = 1; a <= LMT; ++a)
    for (int b = a + 1; b < LMT; ++b)
      for (int d = a + 1; d + b < LMT; ++d)
        if (a * a == 2 * (b - a) * (d - a))
          ++ans;
  for (int a = 1; a <= LMT; ++a)
    for (int b = a + 1; b + b < LMT; ++b) {
      bool t = false;
      for (int x = 1; x < a; ++x)
        if (2 * x * (a - x) == (b - a) * (b - a))
          t = true;
      ans += t;
    }
  printf("%d\n", ans);
  return 0;
}
