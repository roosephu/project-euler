#include <cstdio>
using namespace std;

const int n = 1e6, N = n + 10;

int cnt[100];

int main() {
  for (int i = 1; i <= n / 4; ++i) {
    int L = 0;
    for (int x = 1; x * x < i; ++x) {
      if (i % x == 0) // && (i / x) % 2 == x % 2)
        ++L;
    }
    ++cnt[L];
  }
  int ans = 0;
  for (int i = 1; i <= 10; ++i) {
    ans += cnt[i];
  }
  printf("%d %d\n", ans, cnt[15]);
  return 0;
}
