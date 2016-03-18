#include <cstdio>
#include <cmath>
using namespace std;

const int n = 30;
double cnt[(n + 1) * (n + 1) + 1];

int right(int a, int b, int c) {
  return 0;
}

int gcd(int a, int b) {
  return a ? gcd(b % a, a) : b;
}

int abs(int a) {
  return a > 0 ? a : -a;
}

int main() {
  double ans = 0;
  for (int x0 = 0; x0 <= n; ++x0) {
    printf("progress... %d\n", x0);
    for (int y0 = 0; y0 <= n; ++y0) {
      for (int x1 = 0; x1 <= n; ++x1) {
        for (int y1 = 0; y1 <= n; ++y1) {
          if (x0 == x1 && y0 == y1) {
            continue;
          }

          int points = 0, points2 = 0;
          // for (int x2 = 0; x2 <= n; ++x2)
          //   for (int y2 = 0; y2 <= n; ++y2)
          //     if ((x2 - x0) * (y2 - y1) >= (x2 - x1) * (y2 - y0))
          //       ++points2;

          int multiplier = n * n;
          int a = x1 - x0, b = y1 - y0, c = x0 * y1 - x1 * y0;
          for (int x2 = 0; x2 <= n; ++x2) {
            if (a == 0) {
              if (b * x2 <= c)
                points += n + 1;
              else
                points += 0;
            } else if (a > 0) {
              int lb = (b * x2 - c + a - 1 + a * multiplier) / a - multiplier;
              if (lb < 0) lb = 0;
              if (lb <= n)
                points += (n - lb + 1);
            } else if (a < 0) {
              int ub = (-b * x2 + c + (-a) * multiplier) / (-a) - multiplier;
              if (ub > n) ub = n;
              if (ub >= 0)
                points += ub + 1;
            }
          }
          // if (points != points2) {
          //   printf("points: %d with (%d, %d) and (%d, %d), bf = %d, new = %d\n", points, x0, y0, x1, y1, points2, points);
          // }

          points -= gcd(abs(x0 - x1), abs(y0 - y1)) + 1;

          // ans += (x0 * y1 - x1 * y0) * (1 - pow(n / (n + 1.), points));
          cnt[points] += c;
          // printf("points: %d with (%d, %d) and (%d, %d), gcd = %d\n", points, x0, y0, x1, y1, gcd(abs(x0 - x1), abs(y0 - y1)));
        }
      }
    }
  }
  for (int i = 0; i <= (n + 1) * (n + 1); ++i)
    ans += cnt[i] * (1 - pow(n / (n + 1.), i));
  printf("%.6f\n", ans / (n + 1) / (n + 1) / 2);
  return 0;
}
