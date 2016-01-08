#include <cstdio>
#include <cmath>
#include <set>
using namespace std;

const int n = 120000, N = n + 10;

set<int> G[N];
bool ans[N];

int gcd(int a, int b) {
  return a ? gcd(b % a, a) : b;
}

int main() {
  int cnt = 0;
  for (long long p = 1; p <= n; ++p) {
    if (p % 1000 == 0)
      printf("stage1: %lld\n", p);
    for (long long q = 1; q <= p && p + q <= n; ++q) {
      long long L = p * p + q * q + p * q, l = sqrt(L);
      if (l * l == L) {
        G[p].insert(q);
        // printf("p = %lld, q = %lld, l = %lld\n", p, q, l);
      }
    }
  }

  for (int p = 1; p <= n; ++p) {
    if (p % 1000 == 0)
      printf("stage2: %d\n", p);
    for (auto q : G[p]) {
      for (auto r : G[q]) {
        if (p + q + r > n)
          break;
        if (G[p].count(r) > 0)
          ans[p + q + r] = true;
      }
    }
  }

  long long answer = 0;
  for (int i = 1; i <= n; ++i)
    if (ans[i])
      answer += i;

  printf("%lld\n", answer);
  return 0;
}
