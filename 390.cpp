#include <cstdio>
#include <cmath>
using namespace std;

const long long N = 1e10 * 2;

int main() {
  // for (int a = 1; a <= 10000; ++a)
  //   for (int b = a + 1; b <= 10000; ++b) {
  //     long long s = (a * a + 1ll) * (b * b + 1ll) - 1;
  //     int t = sqrt(s);
  //     if ((long long)t * t == s && b != a + 1 && b != 2 * a * a) {
  //       printf("%d %d %d: %d %d\n", a, b, t, t % b, b / (t % b));
  //     }
  //   }
  long long ans = 0;
  for (long long a = 2; a * a + 1 <= N; a += 2) {
    long long upper_bound = N / (a * a + 1);
    for (long long t = 2; t <= upper_bound; t += 2) {
      if (t % 10000000 == 0)
        printf("%lld %lld\n", t, upper_bound);
      long long s = a * a * t * t - a * a + t * t;
      long long v = sqrt(s);
      if (v * v == s) {
        long long b = a * t + v;
        long long n = a * b + t;
        if (n > N)
          break;
        ans += n / 2;
        // printf("%lld %lld %lld\n", a, b, n);
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}
