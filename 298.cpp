#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

const int n = 50, m = 5;

int randint(int n) {
  for (; ; ) {
    int x = rand();
    if (x / n == RAND_MAX / n)
      continue;
    return x % 10;
  }
  return 0;
}

int simulate() {
  int ret = 0, L[m] = {0}, R[m + 1] = {0};
  for (int i = 1; i <= 50; ++i) {
    int v = randint(10);

    for (int j = m - 1, last = 0; j >= 0; --j) {
      int cur = L[j];
      L[j] = last;
      last = cur;
      if (last == v) {
        ++ret;
        break;
      }
    }

    int s = 0;
    for (int j = 0; j < m; ++j)
      if (R[j] == v) {
        s = 1;
        --ret;
        break;
      }

    if (!s) {
      R[m] = v;
      for (int j = 0; j < m; ++j)
        R[j] = R[j + 1];
    }
  }

  return ret > 0 ? ret : -ret;
}

int main() {
  srand(time(0));

  int nn = 1000000;
  double ans = 0;
  for (int i = 0; i < nn; ++i)
    ans += simulate();

  printf("%.8f\n", ans / nn);

  return 0;
}
