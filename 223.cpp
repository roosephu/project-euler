#include <cstdio>
using namespace std;

const int n = 25000000, N = n + 10;

int primes[N], lnk[N];
int pfac[100], expo[100], top;
long long ans = 0;

int factorize(int n) {
  int ret = 1;
  for (; n != 1; ) {
    int p = lnk[n], e = 0;
    for (; lnk[n] == p; n /= p)
      ++e;
    ++top;
    pfac[top] = p;
    expo[top] = e;
  }
  return ret;
}

void dfs(int dep, long long prod, long long a) {
  if (prod > a)
    return;
  if (dep == 0) {
    long long cp = (a + 1) * (a - 1) / prod;
    if ((cp + prod) % 2 != 0)
      return;
    long long b = (cp - prod) / 2, c = (cp + prod) / 2;
    if (a + b + c <= n && b <= a && a <= c) {
      // if (b != 1)
      //   printf("%lld %lld %lld\n", a, b, c);
      ++ans;
    }
    return;
  }

  // printf("expo: %d\n", expo[dep]);
  for (int i = 0; i <= expo[dep]; ++i) {
    dfs(dep - 1, prod, a);
    prod *= pfac[dep];
  }
}

int main() {
  for (int i = 2; i <= n; ++i) {
    if (!primes[i]) primes[++primes[0]] = i, lnk[i] = i;
    for (int j = 1, k = n / i; primes[j] <= k; ++j) {
      int t = i * primes[j]; primes[t] = 1; lnk[t] = primes[j];
      if (i % primes[j] == 0) break;
    }
  }

  ans = 1; // triangle (1, 1, 1)
  for (long long a = 2; a <= n / 2; ++a) {
    if (a % 100000 == 0)
      printf("progress: %lld\n", a);
    top = 0;

    int e1 = 0, e2 = 0;
    for (; ((a - 1) >> e1 & 1) == 0; )
      ++e1;
    for (; ((a + 1) >> e2 & 1) == 0; )
      ++e2;
    factorize((a - 1) >> e1);
    factorize((a + 1) >> e2);

    ++top;
    pfac[top] = 2;
    expo[top] = e1 + e2;

    dfs(top, 1, a);
    // for (int i = 1; i <= top; ++i)
    //   printf("%d %d\n", pfac[i], expo[i]);
  }
  printf("%lld\n", ans);

  // ans = 0;
  // for (int a = 1; a <= n / 3; ++a)
  //   for (int b = a; a + b <= n; ++b)
  //     for (int c = b; a + b + c <= n; ++c)
  //       if (a * a + b * b == c * c + 1) {
  //         ++ans;
  //         printf("%d %d %d\n", a, b, c);
  //       }
  // printf("%lld\n", ans);

  return 0;
}
