#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int n = 1e6, N = n + 10;
const long long m = 1e12;

bool np[N];

bool is_prime(long long x) {
  if (x <= n) return x >= 2 && !np[x];
  for (long long i = 2; i * i <= x; ++i)
    if (x % i == 0)
      return false;
  return x >= 2;
}

bool contain200(long long x) {
  for (; x >= 200; x /= 10)
    if (x % 1000 == 200)
      return true;
  return false;
}

int main() {
  for (int i = 2; i <= n; ++i) {
    if (np[i] == false) {
      // printf("%d\n", i);
      for (int j = 2; i * j <= n; ++j)
        np[i * j] = true;
    }
  }

  vector<long long> candidates;
  int cnt = 0;
  for (long long p = 2; p <= n && p * p <= m; ++p)
    if (!np[p])
      for (long long q = 2; q <= n && p * p * q * q * q <= m; ++q)
        if (!np[q] && p != q) {
          long long v = p * p * q * q * q;
          if (!contain200(v))
            continue;

          // printf("%lld %lld: %lld\n", p, q, v);
          bool prime_proof = true;
          for (long long d = 1; d <= v; d *= 10) {
            int digit = v / d % 10;
            long long others = v - digit * d;

            for (int i = 0; i < 10; ++i)
              if (i != digit && is_prime(others + i * d)) {
                if (d * 10 > v && i == 0)
                  continue;
                prime_proof = false;
                break;
              }
          }
          if (prime_proof == true) {
            candidates.push_back(v);
            ++cnt;
            printf("%d: %lld\n", cnt, v);
          }
        }

  sort(candidates.begin(), candidates.end());
  printf("ans = %lld\n", candidates[200 - 1]);
  return 0;
}
