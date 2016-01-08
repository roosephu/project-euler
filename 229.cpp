#include <cstdio>
using namespace std;

const int n = 2e9, N = n / 32 + 10;

unsigned int A[N], B[N], C[N], D[N];

#define set(A, i) (A[i >> 5] |= 1u << (i & 31))
#define get(A, i) (A[i >> 5] >> (i & 31) & 1)

int main() {
  for (int a = 1; a * a <= n; ++a)
    for (int b = a; a * a + b * b <= n; ++b) {
      int s = a * a + b * b;
      set(A, s);
    }
  printf("A\n");
  for (int a = 1; a * a <= n; ++a)
    for (int b = 1; a * a + 2 * b * b <= n; ++b) {
      int s = a * a + 2 * b * b;
      set(B, s);
    }
  printf("B\n");
  for (int a = 1; a * a <= n; ++a)
    for (int b = 1; a * a + 3 * b * b <= n; ++b) {
      int s = a * a + 3 * b * b;
      set(C, s);
    }
  printf("C\n");
  for (int a = 1; a * a <= n; ++a)
    for (int b = 1; a * a + 7 * b * b <= n; ++b) {
      int s = a * a + 7 * b * b;
      set(D, s);
    }
  printf("D\n");

  int ans = 0;
  for (int i = 1; i < N; ++i) {
    unsigned int S = A[i] & B[i] & C[i] & D[i];
    for (; S; S &= S - 1)
      ++ans;
  }

  printf("%d\n", ans);
  return 0;
}
