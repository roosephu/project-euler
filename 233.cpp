#include <cstdio>
using namespace std;

const long long n = 1e11, m = 3e5;

int primes[m + 1], used[m];
int o[10];
long long ans = 0, mx = 0;
long long fsum[m];

void dfs2(int dep, long long prod) {
  if (dep == 0) {
    ans += prod * fsum[n / prod];
    return;
  }
  for (int i = 1; i <= primes[0]; ++i) {
    int p = primes[i];
    if (p % 4 != 1 || used[i])
      continue;
    long long pow = prod;
    for (int x = 0; x < o[dep]; ++x) {
      pow *= p;
      if (pow > n)
        return;
    }
    used[i] = true;
    dfs2(dep - 1, pow);
    used[i] = false;
  }
}

void dfs1(int dep, int last, int prod) {
  if (prod == 1) {
    dfs2(dep - 1, 1);
    return;
  }

  for (int i = last + 1; i <= prod; ++i) {
    if (prod % i == 0) {
      o[dep] = (i - 1) / 2;
      dfs1(dep + 1, i, prod / i);
    }
  }
}

int cnt[10000];

int main() {
  // int k = 10000;
  // for (int i = -k; i <= k; ++i)
  //   for (int j = 1 - i; j <= k; ++j)
  //     if ((i * i + j * j) % (i + j) == 0) {
  //       int v = (i * i + j * j) / (i + j);
  //       if (v < 5000) ++cnt[v];
  //     }
  // for (int i = 1; i <= 3000; ++i) {
  //   printf("%d: %d\n", i, cnt[i] + 1);
  //   int ans = 4, t = i;
  //   for (int j = 2; j * j <= t; ++j) {
  //     if (t % j == 0) {
  //       int x = 0;
  //       for (; t % j == 0; t /= j)
  //         ++x;
  //       if (j % 4 == 1)
  //         ans *= 2 * x + 1;
  //     }
  //   }
  //   if (t != 1 && t % 4 == 1)
  //     ans *= 3;
  //   if (ans != cnt[i] + 1)
  //     while (1);
  // }
  for (int i = 2; i <= m; ++i) {
    if (!primes[i]) primes[++primes[0]] = i;
    for (int j = 1, k = m / i; primes[j] <= k; ++j) {
      int t = i * primes[j]; primes[t] = 1;
      if (i % primes[j] == 0) break;
    }
  }
  for (int i = 1; i < m; ++i)
    fsum[i] = i;
  for (int i = 1; i <= primes[0]; ++i) {
    int p = primes[i];
    if (p % 4 == 1)
      for (int x = 1; x * p < m; ++x)
        fsum[x * p] = 0;
  }
  for (int i = 1; i < m; ++i)
    fsum[i] += fsum[i - 1];

  dfs1(1, 1, 420 / 4);
  printf("%lld\n", ans);
  return 0;
}
