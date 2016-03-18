#include <cstdio>
using namespace std;

const int N = 140;
const int MOD = 1e9;
typedef long mat[N][N];
const int coef = [2, -1, 2, 1, 1, 0, -1, 1];

// int search(int state, int cur, int n) {
//   if (state == 0) return cur == n - 1;
//   for (int i = 0, gap = 0; i < n; ++i) {
//     if (state >> i & 1) {
//       gap = 0;
//     } else {
//       ++gap;
//       if (gap == 3 && gap <= i)
//         return 0;
//     }
//   }
//   int ret = 0;
//   for (int i = -3; i <= 3; ++i) {
//     int v = cur + i;
//     if (0 <= v && v < n && (state >> v & 1)) {
//       ret += search(state ^ (1 << v), v, n);
//     }
//   }
//   return ret;
// }

int main() {

  // for (int i = 1; i <= 30; ++i) {
  //   printf("%d %d\n", i, search((1 << i) - 2, 0, i));
  // }

  return 0;
}
