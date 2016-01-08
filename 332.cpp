#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;

const int R = 50, N = 1000;
const double pi = acos(-1), eps = 1e-4;

int x[N], y[N], z[N];

double get_angle(int a, int b, int c) { // angle abc
  long long ax = y[b] * z[a] - y[a] * z[b], ay = z[b] * x[a] - x[b] * z[a], az = x[b] * y[a] - x[a] * y[b];
  long long bx = y[b] * z[c] - y[c] * z[b], by = z[b] * x[c] - x[b] * z[c], bz = x[b] * y[c] - x[c] * y[b];
  long long dot = ax * bx + ay * by + az * bz;
  long long l1 = ax * ax + ay * ay + az * az, l2 = bx * bx + by * by + bz * bz;
  // printf("dot = %lld, l1 = %lld, l2 = %lld\n", dot, l1, l2);
  if (dot * dot == l1 * l2) return -1;
  return acos(dot / sqrt(l1) / sqrt(l2));
}

double solve(int r) {
  int top = 0;
  for (int i = -r; i <= r; ++i)
    for (int j = -r; j <= r; ++j)
      for (int k = -r; k <= r; ++k)
        if (i * i + j * j + k * k == r * r) {
          ++top;
          x[top] = i;
          y[top] = j;
          z[top] = k;
        }

  double ret = 1e300;
  for (int i = 1; i <= top; ++i)
    for (int j = i + 1; j <= top; ++j)
      for (int k = j + 1; k <= top; ++k) {
        double A = get_angle(i, j, k);
        double B = get_angle(j, k, i);
        double C = get_angle(k, i, j);
        if (A < 0 || B < 0 || C < 0)
          continue;

        // double t = get_angle(k, j, i);
        // printf("%.8f %.8f\n", A, t);
        // assert(abs(t - A) <= eps);

        // assert(A + B + C >= pi);
        if (A + B + C < ret) {
          ret = A + B + C;
          // printf("A + B + C = %.6f, a = (%d, %d, %d), b = (%d, %d, %d), c = (%d, %d, %d)\n", A + B + C, x[i], y[i], z[i], x[j], y[j], z[j], x[k], y[k], z[k]);
        }
      }
  ret = (ret - pi) * r * r;
  printf("rad = %d: cnt = %d, ret = %.6f\n", r, top, ret);
  return ret;
}

int main() {
  double ans = 0;
  for (int r = 1; r <= R; ++r) {
    ans += solve(r);
  }
  printf("%.6f\n", ans);
  return 0;
}
