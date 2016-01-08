#include <cstdio>
using namespace std;

typedef long long int64;
typedef unsigned int uint32;

const int N = 1.1e8, n = 1e8;

int lnk[N], primes[N];
int val[100], exp[100], top;
uint32 is_prime[N / 32 + 10];

void sieve(int n){
  for (int i = 2; i <= n; ++i) {
    if (primes[i] == 0) {
      int k = primes[0] + 1;
      primes[k] = i;
      primes[0] = k;
      lnk[i] = i;
      is_prime[i >> 5] |= 1 << (i & 31);
    }
    int k = n / i;
    for (int j = 1; j <= primes[0] && primes[j] <= k; ++j) {
      int t = primes[j] * i;
      primes[t] = 1;
      lnk[t] = primes[j];
      if (i % primes[j] == 0) {
        break;
      }
    }
  }
}

int64 ans = 0;

void dfs(int64 c, int u, int x) {
  if (x == 0) {
    int64 v = (int64)u * u / c - 1;
    c -= 1;
    if (v <= n && (is_prime[v >> 5] >> (v & 31) & 1) == 1 &&
                  (is_prime[c >> 5] >> (c & 31) & 1) == 1) {
      // printf("find one: %lld %d %lld\n", c, u - 1, v);
      ans += c + u + v - 1;
    }
    return;
  }
  for (int i = 0; i <= exp[x]; ++i) {
    dfs(c, u, x - 1);
    c *= val[x];
    if (c >= u)
      break;
  }
}

int main() {
  sieve(n);
  for (int i = 1; i <= primes[0]; ++i) {
    top = 0;
    for (int u = primes[i] + 1; u != 1; ) {
      int x = lnk[u];
      top += 1;
      val[top] = x;
      exp[top] = 0;
      while (x == lnk[u]) {
        exp[top] += 2;
        u /= x;
      }
      // printf("%d: %d %d\n", primes[i] + 1, val[top], exp[top]);
    }
    if (i % 10000 == 1)
      printf("%d/%d\n", i, primes[0]);
    dfs(1, primes[i] + 1, top);
  }
  printf("%lld\n", ans);
  return 0;
}
