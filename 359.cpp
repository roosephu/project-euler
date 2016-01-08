#include <cstdio>
using namespace std;

int P(int r, int f) {
  int first = r * r / 2, start = r / 2 * 2 + 1;
  if (r == 1) ++f;
  if (f % 2 == 0) {
    first = start * start - first;
    ++start;
    --f;
  }
  return first + (start + start + f - 2) * (f - 1) / 2;
}

int main() {
  printf("%d %d %d %d %d\n", P(10, 20), P(99, 100), P(25, 75), P(1, 1), P(1, 2));
  return 0;
}
