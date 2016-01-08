#include <cstdio>
#include <cmath>
using namespace std;

const int n = 1e9;

int gcd(int a, int b) {return a ? gcd(b % a, a) : b;}

int main() {
  long long ans = 0;
  for (int aa = 1; aa <= n / aa / aa / aa; ++aa)
    for (int bb = aa; bb <= n; ++bb) {
      long long K = n / bb / bb / (aa + bb) / (aa + bb);
      if (K == 0) break;
      if (gcd(aa, bb) != 1) continue;
      int a = aa * aa * (aa + bb) * (aa + bb);
      int b = bb * bb * (aa + bb) * (aa + bb);
      int c = aa * aa * bb * bb;
      printf("%d %d %d %lld\n", a, b, c, K);
      ans += (K + 1) * K / 2 * (a + b + c);
      // for (int k = 1; k <= K; ++k) {
      //   int a = k * aa * aa * (aa + bb) * (aa + bb);
      //   int b = k * bb * bb * (aa + bb) * (aa + bb);
      //   int c = k * aa * aa * bb * bb;
      //   ans += a + b + c;
      //   printf("%.3lf + %.3lf = %.3lf vs %.3lf | a = %d, b = %d, c = %d\n", 1 / sqrt(a), 1 / sqrt(b), 1 / sqrt(a) + 1  / sqrt(b), 1 / sqrt(c), a, b, c);
      // }
    }
  printf("%lld\n", ans);
  return 0;
}
