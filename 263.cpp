#include <cstdio>
#include <algorithm>
using namespace std;

const int n = 1e8, N = n + 10;

int primes[N];
int dvs[10000], top;

void dfs(int n, int last, int d) {
  if (n == 1) {
    dvs[++top] = d;
    return;
  }

  int p = primes[n];
  dfs(n / p, p - 1, d);
  if (p <= last)
    dfs(n / p, p, d * p);
}

bool practical(int n) {
  top = 0;
  dfs(n, n + 1, 1);
  sort(dvs + 1, dvs + top + 1);
  for (long long i = 1, s = 0; i < top; ++i) {
    if (dvs[i] > s + 1)
      return false;
    s += dvs[i];
  }
  return true;
}

bool is_prime(int n) {
  return primes[n] == n;
}

int main() {
  for (int i = 2; i <= n; ++i)
    if (!primes[i])
      for (int j = 1; i * j <= n; ++j)
        primes[i * j] = i;

  for (int i = 10; i <= n; i += 10) {
    if (is_prime(i - 9) &&
        is_prime(i - 3) &&
        is_prime(i + 3) &&
        is_prime(i + 9)) {
      // printf("step 1: %d\n", i);
      if (practical(i - 8) &&
          practical(i - 4) &&
          practical(i) &&
          practical(i + 4) &&
          practical(i + 8)) {
        printf("ans += %d\n", i);
      }
    }
  }
  return 0;
}
