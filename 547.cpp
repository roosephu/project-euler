#include <cstdio>
#include <cmath>
using namespace std;

const int n = 40, N = n + 2;

double f_1[N][N], f_x[N][N], f_y[N][N], f_xy[N][N];

int abs(int x) {
  return x > 0 ? x : -x;
}

double ff(int type, double dx, double dy) {
  if (type == 0) {
    return (dy > 0 ? pow(dy, 3) * asinh(dx / dy) / 6 : 0) + (dx > 0 ? pow(dx, 3) * asinh(dy / dx) / 6 : 0) + sqrt(dx * dx + dy * dy) * dx * dy / 3;
  } else if (type == 1) {
    return (dy > 0 ? pow(dy, 4) * asinh(dx / dy) / 8 : 0) + (2 * pow(dx, 3) + 5 * dx * dy * dy) * sqrt(dx * dx + dy * dy) / 24;
  } else if (type == 2) {
    return (dx > 0 ? pow(dx, 4) * asinh(dy / dx) / 8 : 0) + (2 * pow(dy, 3) + 5 * dy * dx * dx) * sqrt(dx * dx + dy * dy) / 24;
  } else if (type == 3) {
    return pow(dx * dx + dy * dy, 2.5) / 15;
  }
  printf("...\n");
  return 0;
}

double integral(double (*f)[N], int lx, int rx, int ly, int ry) {
  return f[rx][ry] - f[lx][ry] - f[rx][ly] + f[lx][ly];
}

double F(int a, int b) { // max(dx, a) * max(dy, b)
  double ret = 0;
  ret += integral(f_1, 0, a, 0, b) * a * b;
  ret += integral(f_x, a, n, 0, b) * b;
  ret += integral(f_y, 0, a, b, n) * a;
  ret += integral(f_xy, a, n, b, n);
  return ret;
}

double G(int a, int b) { // (x - a) * (y - b)
  double ret = 0;
  ret += integral(f_1, 0, a, 0, b) * a * b;
  ret -= integral(f_x, 0, a, 0, b) * b;
  ret -= integral(f_y, 0, a, 0, b) * a;
  ret += integral(f_xy, 0, a, 0, b);
  return ret;
}

int main() {
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j) {
      f_1[i][j] = ff(0, i, j);
      f_y[i][j] = ff(1, i, j);
      f_x[i][j] = ff(2, i, j);
      f_xy[i][j] = ff(3, i, j);
    }
  printf("%.4f\n", integral(f_xy, 0, 2, 0, 3));
  double ans = 0;
  for (int lx = 1; lx < n; ++lx)
    for (int rx = lx + 1; rx < n; ++rx)
      for (int ly = 1; ly < n; ++ly)
        for (int ry = ly + 1; ry < n; ++ry) {
          int px = rx - lx, py = ry - ly;
          // printf("%d %d %d %d\n", lx, rx, ly, ry);
          double area = n * n - px * py;

          double cur = 0;

          // (n - dx) * (n - dy)
          cur += G(n, n);

          // (max(dx, n - lx) - max(dx, n - rx)) * (max(dy, n - ly) - max(dy, n - ry))
          cur -= F(n - lx, n - ly);
          cur += F(n - lx, n - ry);
          cur += F(n - rx, n - ly);
          cur -= F(n - rx, n - ry);

          // (max(dx, rx) - max(dx, lx)) * (max(dy, ry) - max(dy, ly))
          cur -= F(rx, ry);
          cur += F(rx, ly);
          cur += F(lx, ry);
          cur -= F(lx, ly);

          // (px - dx) * (py - dy)
          cur += G(px, py);

          ans += cur * 4 / area / area;
        }
  printf("%.4f\n", ans);

  return 0;
}
