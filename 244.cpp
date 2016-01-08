#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int N = 16;
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1}, weight[] = {'U', 'D', 'L', 'R'};
const int MOD = 100000007;

int dist[N][1 << N];
long long chk[N][1 << N];
int queue[N * (1 << N)];
int beg = 0, end = 0;

void push(int pos, int state, int d, long long chksum) {
  if (dist[pos][state] > d) {
    ++end;
    dist[pos][state] = d;
    chk[pos][state] = chksum;
    queue[end] = pos << N | state;
  } else if (dist[pos][state] == d) {
    (chk[pos][state] += chksum) %= MOD;
  }
}

int main() {
  int init_state = 0, final_state = 0;
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j) {
      if ((i + j) % 2 == 1)
        final_state |= 1 << (4 * i + j);
      if (j >= 2)
        init_state |= 1 << (4 * i + j);
    }

  memset(dist, 0x3f, sizeof(dist));
  push(0, init_state, 0, 0);

  for (; beg < end; ) {
    ++beg;
    int pos = queue[beg] >> N, state = queue[beg] & ((1 << N) - 1);
    int x = pos >> 2, y = pos & 3;
    long long chksum = (chk[pos][state] * 243ll) % MOD;
    for (int i = 0; i < 4; ++i) {
      int nx = x + dx[i], ny = y + dy[i], npos = 4 * nx + ny;
      if (0 <= nx && nx < 4 && 0 <= ny && ny < 4) {
        int b = state >> npos & 1;
        int ns = (state ^ (b << npos)) | (b << pos);
        push(4 * nx + ny, ns, dist[pos][state] + 1, chksum + weight[i]);
      }
    }
  }
  printf("%d %lld\n", dist[0][final_state], chk[0][final_state]);
  return 0;
}
