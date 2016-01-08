#include <cstdio>
#include <map>
using namespace std;

#define fst first
#define snd second

const long long n = (long long)1e16, N = 100;

map<long long, int> f[N];
long long cb[N][N];
long long cnt[N];

bool is_prime(int n) {
  for (int i = 2; i * i <= n; ++i)
    if (n % i == 0)
      return false;
  return n != 1;
}

int main() {
  f[0][n] = 1;

  int T = 0;
  for (int i = 2; i <= 100; ++i) {
    if (is_prime(i)) {
      for (int x = T; x >= 0; --x) {
        for (auto p : f[x]) {
          long long w = p.fst / i;
          if (w == 0)
            continue;
          if (f[x + 1].count(w))
            f[x + 1][w] += p.snd;
          else
            f[x + 1][w] = p.snd;
        }
        printf("%d ", (int)f[x].size());
      }
      printf("\n");
      ++T;
    }
  }

  for (int i = 0; i <= T; ++i)
    for (int j = 0; j <= i; ++j)
      cb[i][j] = j ? cb[i - 1][j - 1] + cb[i - 1][j] : 1;
  for (int x = 4; x <= T; ++x)
    for (auto p : f[x])
      cnt[x] += p.fst * p.snd;
  for (int x = T; x >= 4; --x)
    for (int y = x + 1; y <= T; ++y)
      cnt[x] -= cnt[y] * cb[y][x];
  long long ans = 0;
  for (int i = 4; i <= T; ++i)
    ans += cnt[i];

  printf("%lld\n", ans);
  return 0;
}
