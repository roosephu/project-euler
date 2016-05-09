#include <cstdio>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;

// const int n = 10000000, N = n + 10;
const long n = 1e17;

struct node {
  long pos, val, mul;
  int base, exp;

  node(int _base, int _exp, long _mul) :
    base(_base), exp(_exp), mul(_mul) {

    pos = 1;
    for (int i = 1; i <= exp; ++i) {
      pos *= base;
    }
    long pow = pos;
    val = 0;
    for (int i = 0; i <= exp; ++i) {
      val += pow;
      pow = pow / base * (base - 1);
    }

    if (pos == 0 || val == 0) {
      printf("xxx, base = %d, exp = %d\n", base, exp);
    }
  }
};

// int f[n + 10], g[n + 10], h[n + 10];

bool operator < (node a, node b) {
  if (a.pos * a.mul != b.pos * b.mul)
    return a.pos * a.mul < b.pos * b.mul;
  return a.val * a.mul > b.val * b.mul;
}

multiset<node> f;

int main() {
  // for (int a = 2; a * a <= n; ++a)
  //   for (long long p = a * a; p <= n; p *= a) {
  //     int s = 0;
  //     for (int q = p; ; ) {
  //       s += q;
  //       if (q % a != 0)
  //         break;
  //       q = q / a * (a - 1);
  //     }
  //     for (int c = 1; c * p <= n; ++c)
  //       if (c * s > f[c * p]) {
  //         f[c * p] = c * s;
  //         g[c * p] = p;
  //         h[c * p] = a;
  //       }
  //   }
  // int mx = 0;
  // for (int i = 4, cnt = 1; i <= n; ++i) {
  //   if (f[i] > mx) {
  //     mx = f[i];
  //     printf("cnt = %d, %d: %d using %d^%d\n", cnt, i, f[i], h[i], (int)(log(g[i]) / log(h[i]) + 0.1));
  //     cnt += 1;
  //   }
  // }

  // a tuple = <trigger, answer, base, exp>
  long min_exp = 2, min_base = 2;
  for (int i = 2; i <= 90; ++i) {
    long p = i;
    for (int j = 2; p <= n; ++j) {
      p *= i;
      f.insert(node(i, j, 1));
    }
  }

  long cur = 0, last_fpos = 0;
  long ans = 0;

  int cnt = 0;
  for ( ; !f.empty(); ) {
    auto it = f.begin();
    auto x = *it;
    f.erase(it);
    if (x.pos * x.mul > n)
      break;
    // if (x.mul == 1)
    //   f.insert(node(x.base + 1, x.exp, 1));
    // if (x.base - 1 == x.mul) {
    //   // printf("%d %d\n", x.base, x.exp);
    //   f.insert(node(x.base, x.exp + 1, 1));
    // }

    // if (x.base < min_base || x.exp < min_exp)
    //   continue;
    // cur = x.val;

    min_base = max(min_base, x.val / x.pos);
    min_exp = max(min_exp, x.val / x.pos - 1);

    if (cur < x.val * x.mul) {
      // count from last_pos to pos, the answer is cur
      long pos = x.pos * x.mul, fpos = pos & 1 ? -1 : 0;
      ans += (fpos - last_fpos) * cur;
      last_fpos = fpos;

      cur = x.val * x.mul;
      cnt += 1;
      printf("cnt = %d, pos = %ld, val = %ld, base = %d, exp = %d, f.size() = %d, min base = %ld, min exp = %ld\n", cnt, x.pos * x.mul, x.val * x.mul, x.base, x.exp, (int)f.size(), min_base, min_exp);

    }

    x.mul = max((cur - 1) / x.val, x.mul) + 1;
    f.insert(x);
  }

  long fpos = (n + 1) % 2 == 1 ? -1 : 0;
  ans += (fpos - last_fpos) * cur;
  printf("ans = %ld\n", -ans);

  return 0;
}
