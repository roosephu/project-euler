#include <cstdio>
#include <vector>
using namespace std;

#define fst first
#define snd second

const int n = 50000, N = n + 10, max_x = 10000 + 399;

vector<int> box[max_x + 10];
int S[N * 6 + 10];
int lx[N], rx[N], ly[N], ry[N], lz[N], rz[N];

int solve(vector<int> &box, int y) {
  vector<pair<int, int>> events;
  for (auto k : box) {
    if (ly[k] <= y && y < ry[k]) {
      events.push_back(make_pair(lz[k], +1));
      events.push_back(make_pair(rz[k], -1));
    }
  }
  sort(events.begin(), events.end());

  int cnt = 0, ret = 0, last = 0;
  for (auto &evt : events) {
    int pos = evt.fst;
    if (cnt > 0)
      ret += pos - last;
    last = pos;
    cnt += evt.snd;
  }

  return ret;
}

int main() {
  for (int i = 1; i <= 55; ++i)
    S[i] = (100003ll - 200003ll * i + 300007ll * i * i * i) % 1000000;
  for (int i = 56; i <= n * 6; ++i)
    S[i] = (S[i - 24] + S[i - 55]) % 1000000;

  for (int i = 1; i <= n; ++i) {
    lx[i] = S[6 * i - 5] % 10000;
    ly[i] = S[6 * i - 4] % 10000;
    lz[i] = S[6 * i - 3] % 10000;
    rx[i] = S[6 * i - 2] % 399 + lx[i] + 1;
    ry[i] = S[6 * i - 1] % 399 + ly[i] + 1;
    rz[i] = S[6 * i - 0] % 399 + lz[i] + 1;

    for (int x = lx[i]; x < rx[i]; ++x)
      box[x].push_back(i);
  }

  long long complexity = 0, ans = 0;
  for (int x = 0; x < max_x; ++x) {
    if (x % 1000 == 0)
      printf("current: %d\n", x);
    vector<int> events;
    for (auto k : box[x]) {
      events.push_back(ly[k]);
      events.push_back(ry[k]);
    }
    sort(events.begin(), events.end());

    for (int y = 0; y < (int)events.size() - 1; ++y) {
      int cy = events[y], ny = events[y + 1];
      ans += (ny - cy) * solve(box[x], cy);
    }
  }
  printf("%lld\n", ans);
  return 0;
}
