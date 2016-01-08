#include <cstdio>
using namespace std;

const int n = 1000, N = n + 10;

int s[N][N];
long long f[N];

int main() {
  long long t = 0, ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) {
      t = (615949 * t + 797807) % (1 << 20);
      s[i][j] = t - (1 << 19);
    }
    for (int j = 0; j <= n; ++j)
      f[j] = 0;
    for (int j = i; j; --j) {
      long long sum = 0;
      for (int k = j; k <= i; ++k) {
        f[k] += s[i + j - k][j];
        sum += f[k];
        if (sum < ans)
          ans = sum;
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}
