#include <cstdio>
using namespace std;

const int N = 1000000;

int cnt[N];

int main() {
  for (int i = 1; i <= 1000; ++i)
    for (int j = i; i * j < N; ++j)
      for (int k = j; k < N / (i + j); ++k) {
        int A = 2 * (i * j + j * k + k * i);
        if (A > N) break;
        int B = 4 * (i + j + k);
        int C = 8;
        while (A < N) {
          ++cnt[A];
          A += B;
          B += C;
        }
      }

  for (int i = 1; i < N; ++i) {
    if (cnt[i] == 1000) {
      printf("%d\n", i);
      break;
    }
  }
  return 0;
}
