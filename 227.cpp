#include <cstdio>
using namespace std;

const int n = 100;
const double eps = 1e-13;

double f[n];

int main() {
  for (bool b = true; b; ) {
    b = false;
    for (int i = 1; i < n; ++i) {
      double d = (f[(i + n - 2) % n] + f[i - 1] * 8 + f[(i + 1) % n] * 8 + f[(i + 2) % n]) / 18 + 2;
      if (f[i] > d + eps || f[i] < d - eps)
        f[i] = d, b = true;
    }
    printf("%.10f %.10f %.10f\n", f[n / 2 - 1], f[n / 2], f[n / 2 + 1]);
  }
  return 0;
}
