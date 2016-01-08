#include <cstdio>
#include <algorithm>
using namespace std;

int x[10];

int main() {
  for (int i = 0; i < 10; ++i)
    x[i] = i + 1;

  do {
    bool b = true;
    int s = x[0] + x[1] + x[5];
    for (int i = 0; i < 5; ++i) {
      if (x[i] + x[(i + 1) % 5] + x[i + 5] != s || x[i] == 10) {
        b = false;
        break;
      }
    }
    if (b) {
      int minimum = -1;
      for (int i = 5; i < 10; ++i)
        if (minimum == -1 || x[i] < x[minimum])
          minimum = i;
      for (int i = 0; i < 5; ++i) {
        int idx = (minimum + i) % 5;
        printf("%d%d%d", x[idx + 5], x[idx], x[(idx + 1) % 5]);
      }
      printf("\n");
    }
  } while (next_permutation(x, x + 10));
  return 0;
}
