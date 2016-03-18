#include <cstdio>
#include <vector>
#include <set>
using namespace std;

const int n = 1e1, N = n + 10;

int f[N], primes[N], lnk[N], cnt[N];

int main() {
  for (int i = 2; i <= n; ++i) {
    if (!primes[i]) primes[++primes[0]] = i, lnk[i] = i;
    for (int j = 1, k = n / i, t; primes[j] <= k; ++j) {
      primes[t = i * primes[j]] = 1, lnk[t] = primes[j];
      if (i % primes[j] == 0) break;
    }
  }
  for (int i = 2; i <= n; ++i) {
    int rep = 1;
    vector<int> exp;
    for (int j = i, idx = 1; j != 1; ++idx) {
      int p = lnk[j], e = 0;
      for (; lnk[j] == p; j /= p)
        ++e;
      exp.push_back(e);
    }
    sort(exp.rbegin(), exp.rend());
    for (int a = 0; a < exp.size(); ++a)
      for (int k = 0; k < exp[a]; ++k)
        rep *= primes[a + 1];

    if (rep != i)
      f[i] = f[rep];
    else {
      vector<int> factors;
      for (int t = 1; t * t <= i; ++t)
        if (i % t == 0) {
          factors.push_back(t);
          if (t * t != i)
            factors.push_back(i / t);
        }

      set<int> mex;
      for (auto a : factors)
        if (a != 1 && a != i)
          for (auto b : factors)
            if (b != 1 && b != i)
              mex.insert(f[a] ^ f[b]);

      f[i] = 0;
      for (; mex.count(f[i]) == 1; )
        ++f[i];
      printf("alone %d: %d\n", i, f[i]);
    }
    ++cnt[f[i]];
  }
  printf("[");
  for (int i = 0; i < 64; ++i) {
    printf("%d, ", cnt[i]);
  }
  printf("]\n");

  return 0;
}
