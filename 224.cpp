#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

#define fst first
#define snd second

const int n = 75000000, N = n + 10, sqrt_n = 9000;

bool not_prime[N];
int primes[N], lnk[N];
vector<pair<int, int>> f[N];
int val[100], top;
int ans = 0;

pair<int, int> compose(pair<int, int> a, pair<int, int> b) {
  return make_pair(a.fst * b.fst + a.snd * b.snd, a.fst * b.snd - a.snd * b.fst);
}

void dfs(int dep, int c, pair<int, int> p) {
  if (dep == 0) {
    if (0 < p.fst && p.fst <= p.snd) {
      int sum = 2 * p.fst + 2 * p.snd + c * 2 + 1;
      if (sum <= n) {
        // printf("%d %d %d: %lld vs %lld\n", 2 * p.fst, 2 * p.snd, c * 2 + 1, 1ll * p.fst * p.fst + 1ll * p.snd * p.snd, 1ll * c * c + 1 * c);
        ++ans;
      }
    }
    return ;
  }

  for (auto &q : f[val[dep]])
    dfs(dep - 1, c, compose(p, q));
}

int factorize(int n) {
  int ret = 1;
  for (; n != 1; ) {
    int p = lnk[n], c = 1, e = 0;
    for (; lnk[n] == p; n /= p)
      c *= p, ++e;
    if (p % 4 == 3) {
      if (e % 2 == 1)
        return 0;
      for (; e; e -= 2)
        ret *= p;
    } else {
      ++top;
      val[top] = c;
    }
  }
  return ret;
}

int main() {
  for (int i = 2; i <= n; ++i) {
    if (!not_prime[i]) primes[++primes[0]] = i, lnk[i] = i;
    for (int j = 1, k = n / i; primes[j] <= k; ++j) {
      int t = i * primes[j]; not_prime[t] = 1; lnk[t] = primes[j];
      if (i % primes[j] == 0) break;
    }
  }
  printf("stage 1 done...\n");
  for (int i = 1; i <= primes[0]; ++i) {
    long long p = primes[i];
    for (; p <= n; p *= primes[i])
      not_prime[p] = false;
  }
  for (int a = 0; a <= sqrt_n; ++a)
    for (int b = 1; b <= sqrt_n; ++b) {
      int s = a * a + b * b;
      if (s <= n && !not_prime[s])
        f[s].push_back(make_pair(a, b));
    }
  // printf("%d\n", f[5].size());
  // printf("%d\n", f[5 * 5].size());
  // printf("%d\n", f[5 * 5 * 5].size());
  // printf("%d\n", f[5 * 5 * 5 * 5].size());
  // printf("%d\n", f[5 * 5 * 5 * 5 * 5].size());
  printf("stage 2 done...\n");

  for (int c = 1; c <= n / 4; ++c) {
    top = 0;
    int basic = factorize(c);
    basic *= factorize(c + 1);
    if (basic == 0)
      continue;

    dfs(top, c, make_pair(+basic, 0));
    dfs(top, c, make_pair(-basic, 0));
    dfs(top, c, make_pair(0, +basic));
    dfs(top, c, make_pair(0, -basic));
  }
  printf("%d\n", ans);
  return 0;

  ans = 0;
  for (int a = 1; a <= n; ++a)
    for (int b = a; b <= n; ++b) {
      int c = sqrt(a * a + b * b + 1);
      if (c * c - 1 == a * a + b * b && a + b + c <= n) {
        ++ans;
        printf("%d %d %d\n", a, b, c);
      }
    }
  printf("%d\n", ans);
  return 0;
}
