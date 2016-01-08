#include <cstdio>
using namespace std;

long long f[100];
bool o[100];

int main() {
  long long ans = 1;
  f[0] = 1, f[1] = 1;
  for (int i = 2; i <= (1 << 6); ++i)
    f[i] = f[i - 1] + f[i - 2];
  for (int i = 0; i < (1 << 6); ++i) {
    if (o[i]) continue;
    int cnt = 0;
    printf("-----\n");
    for (; !o[i]; ) {
      o[i] = true;
      cnt += 1;
      int a = i >> 5 & 1;
      int b = i >> 4 & 1;
      int c = i >> 3 & 1;
      int next = ((i << 1) & 0x3f) | (a ^ (b & c));
      for (int x = 5; x >= 0; --x)
        printf("%d", i >> x & 1);
      printf("\n");
      i = next;
    }

    printf("loop: %d\n", cnt);
    ans = ans * (f[cnt] + (cnt >= 2 ? f[cnt - 2] : 0));
  }
  printf("%lld\n", ans);
  return 0;
}
