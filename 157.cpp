#include <cstdio>
using namespace std;

long long power(int b, int e) {
  return e ? b * power(b, e - 1) : 1;
}

int dvs(long long x) {
  int t = 1;
  for (long long i = 2; i * i <= x; ++i) {
    int cnt = 1;
    for (; x % i == 0; x /= i)
      ++cnt;
    t *= cnt;
  }

  if (x != 1)
    t *= 2;
  return t;
}

int main() {
  int ans = 0;
  for (int n = 1; n <= 9; ++n)
    for (int a2 = 0; a2 <= 0; ++a2)
      for (int b2 = 0; a2 + b2 <= n; ++b2)
        if (a2 == 0 || b2 == 0)
          for (int a5 = 0; a5 <= (b2 ? n : 0); ++a5)
            for (int b5 = 0; a5 + b5 <= n; ++b5)
              if (a5 == 0 || b5 == 0)
                ans += dvs((power(2, a2) * power(5, a5) + power(2, b2) * power(5, b5)) * power(2, n - a2 - b2) * power(5, n - a5 - b5));
  printf("%d\n", ans);
  return 0;
}
