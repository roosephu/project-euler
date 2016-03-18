#include <cstdio>
using namespace std;

const int n = 80846691 * 2, N = n + 100;
const long m = 2e15;

int p[N], cursor, y[N / 2];

void push(int x) {
  int digits[10], t = 0;
  for (; x; x /= 10)
    digits[++t] = x % 10;

  for (int i = t; i; --i) {
    y[++y[0]] = digits[i];
    cursor += digits[i];
    p[cursor] = 1;
  }
}

int main() {
  long s0 = 14025256;

  for (long x = s0; ; ) {
    push(x);
    x = x * x % 20300713;
    if (x == s0)
      break;
  }
  for (int i = 1; i <= y[0]; ++i) {
    y[i + y[0]] = y[i];
    cursor += y[i];
    p[cursor] = 1;
  }
  cursor /= 2;
  // for (int i = 1; i <= 20; ++i)
  //   printf("%d", y[i]);

  p[0] = 1;
  for (int i = 1; i <= cursor; ++i) {
    if (i % 1000000 == 0) {
      printf("progress: %d\n", i);
    }
    for (int t = 0, j = 1; t + i <= cursor * 2; t += y[j], ++j) {
      if (p[t + i] == 1) {
        // printf("i = %d, j = %d, t = %d\n", i, j, t);
        // if ((p[i] == 1) != (j == 1))
        //   while (true);
        p[i] = j;
        break;
      }
    }
  }
  // for (int i = 1; i <= cursor; ++i)
  //   if (p[i] != p[i + cursor]) {
  //     printf("Fail: i = %d, p[i] = %d, p[i + ..] = %d\n", i, p[i], p[i + cursor]);
  //     while (true);
  //   }

  long ans = 0;
  // for (int i = 1; i <= 1000; ++i) {
  //   // printf("%d: %d\n", i, p[i]);
  //   ans += p[i];
  // }
  for (int i = 1; i <= cursor; ++i)
    ans += p[i];
  ans = ans * (m / cursor);
  for (int i = 1; i <= m % cursor; ++i)
    ans += p[i];
  printf("%ld\n", ans);
  return 0;
}
