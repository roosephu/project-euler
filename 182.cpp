#include <cstdio>
#include <algorithm>
using namespace std;

int cnt_p[10000], cnt_q[10000];

int gcd(int a, int b) {
  return a ? gcd(b % a, a) : b;
}

int fpm(int b, int e, int m) {
  int t = 1;
  for (; e; e >>= 1, b = b * b % m)
    e & 1 ? t = t * b % m : 0;
  return t;
}

int main() {
  int p = 1009, q = 3643;
  // int p = 19, q = 37;
  for (int e = 0; e < p - 1; ++e) {
    for (int i = 0; i < p; ++i) {
      cnt_p[e] += fpm(i, e, p) == i;
    }
  }

  for (int e = 0; e < q - 1; ++e) {
    for (int i = 0; i < q; ++i) {
      cnt_q[e] += fpm(i, e, q) == i;
    }
  }

  int phi = (p - 1) * (q - 1), min_ans = phi;
  long long ans = 0;
  for (int e = 2; e < phi; ++e)
    if (gcd(e, phi) == 1)
      min_ans = min(min_ans, cnt_p[e % (p - 1)] * cnt_q[e % (q - 1)]);

  for (int e = 2; e < phi; ++e)
    if (gcd(e, phi) == 1 && cnt_p[e % (p - 1)] * cnt_q[e % (q - 1)] == min_ans)
      ans += e;

  printf("%lld\n", ans);
  return 0;
}
