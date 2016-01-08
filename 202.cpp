#include <cstdio>
using namespace std;

const long long n = 12017639147ll;

int top;
long long factor[100];
long long lmt, ans;

long long gcd(long long a, long long b) {
  return a ? gcd(b % a, a) : b;
}

void dfs(int d, long long dvs, int mu) {
  if (d == 0) {
    if (dvs != 1 && dvs != 2) {
      long long cnt = lmt / dvs / 3;
      for (long long x = dvs; x <= lmt % (dvs * 3); x += dvs)
        if (x % 3 == 2)
          ++cnt;
      ans += mu * cnt;
      printf("current divisor: %lld, cnt = %lld\n", dvs, cnt);
    }
    return;
  }

  dfs(d - 1, dvs            , +mu);
  dfs(d - 1, dvs * factor[d], -mu);
}

int main() {
  long long t = (n + 3) / 6;
  if ((n + 3 - 6 * t) % 4 != 0)
    --t;

  long long x0 = (n + 3 - 6 * t) / 4, y0 = (n + 3 + 6 * t) / 4;
  printf("x0 = %lld, y0 = %lld, diff = %lld\n", x0, y0, (y0 - x0) / 3);

  long long nn = (n + 3) / 2;
  lmt = nn;
  for (long long i = 2; i * i <= nn; ++i)
    if (nn % i == 0) {
      for (; nn % i == 0; )
        nn /= i;

      factor[++top] = i;
    }
  if (nn != 1)
    factor[++top] = nn;
  for (int i = 1; i <= top; ++i)
    printf("prime factors: %lld\n", factor[i]);

  ans = (y0 - x0) / 3 + 1;
  dfs(top, 1, 1);

  // for (long long x = x0, y = y0; x <= y0; x += 3, y -= 3) {
  //   if (x % 9999999 == 2)
  //     printf("progess: %lld\n", x);
  //   if (gcd(x, y) == 1)
  //     ++ans;
  // }
  printf("ans = %lld\n", ans);
  return 0;
}
