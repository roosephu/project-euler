#include <cstdio>
#include <cmath>
using namespace std;

int main() {
  double g = 9.81, pi = acos(-1), y0 = 100, v = 20;
  double x = v / g * sqrt(v * v + 2 * g * y0);
  printf("%.6lf\n", pi / g * (x * x * (v * v + 2 * g * y0) / 2 - x * x * x * x * g * g / v / v / 4));
  return 0;
}
