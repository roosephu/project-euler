#include <cstdio>
using namespace std;

const int n = 500, N = n + 10, S = 15;

int is_prime[N];
char snd[] = "PPPPNNPPPNPPNPN";

long long gcd(long long a, long long b) {
  return a ? gcd(b % a, a) : b;
}

int dfs(int x, int s, int p) {
  if (s == 0)
    return p;
  if (is_prime[x] == (snd[S - s] == 'P'))
    p *= 2;
  if (x == 1)
    return dfs(x + 1, s - 1, 2 * p);
  if (x == n)
    return dfs(x - 1, s - 1, 2 * p);
  return dfs(x + 1, s - 1, p) + dfs(x - 1, s - 1, p);
}

int main() {
  for (int i = 2; i <= 500; ++i) {
    is_prime[i] = true;
    for (int j = 2; j * j <= i; ++j)
      if (i % j == 0) {
        is_prime[i] = false;
        break;
      }
  }

  long long ans = 0, deno = n;
  for (int i = 1; i <= n; ++i) {
    ans += dfs(i, S, 1);
  }
  for (int i = 1; i <= S; ++i)
    deno *= 6;
  long long g = gcd(ans, deno);
  printf("%lld/%lld\n", ans / g, deno / g);
  return 0;
}
