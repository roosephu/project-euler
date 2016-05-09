#include <cstdio>
using namespace std;

const long N = (1l << 31), n = 31;

unsigned int bits[N / 32];

#define get_bit(x, y) (x[(y) >> 5] >> ((y) & 31) & 1)
#define set_bit(x, y) (x[(y) >> 5] |= 1u << ((y) & 31))

long solve(long n) {
  int pattern = -1;
  for (int i = 0; i < n / 32 + 1; ++i)
    bits[i] = 0;

  long ret = 0;
  for (long x = 0, y = n -1; x < n; ++x) {
    int cnt = 0;
    for (++y; y >= 0; --y) {
      if (y * y + x * x >= n * n)
        continue;
      if ((n - 1) * (n - 1) <= y * y + x * x) {
        // printf("%d %d\n", x, y);
        ++cnt;
      } else
        break;
    }

    if (cnt % 2 == 1) {
      ++ret;
      set_bit(bits, x);
    }

    if (pattern == -1) {
      pattern = cnt;
    } else if (pattern % 2 != cnt % 2 && n % 2 == 1) {
      printf("FAIL\n");
      return 0;
    }
  }

  ret = ret * (n - ret) * 2;
  for (long x = 0, y = n -1; x < n; ++x) {
    for (++y; y >= 0; --y) {
      if (y * y + x * x >= n * n)
        continue;
      if ((n - 1) * (n - 1) <= y * y + x * x) {
        int now = get_bit(bits, x) ^ get_bit(bits, y);
        if (now == 1)
          ret -= 1;
        else
          ret += 1;
      } else
        break;
    }
  }

  return ret;
}

int main() {
  long ans = 3;
  for (int i = 4; i <= n; i += 2) {
    printf("checking %d\n", i);
    long now = solve((1l << i) - i);
    ans += now;
  }
  printf("%ld\n", ans);
  return 0;
}
