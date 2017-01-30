#include "fmt/format.h"
#include <NTL/ZZ.h>
#include <queue>
using namespace std;
using namespace NTL;
using namespace fmt;

const int n = 2500000, N = n + 100;

double x[N], y[N];
deque<int> Q[N];
int ans = 0;

double cross(int a, int b, int c) {
    return (x[b] - x[a]) * (y[c] - y[a]) - (x[c] - x[a]) * (y[b] - y[a]);
}

void proceed(int i, int j) {
    while (!Q[i].empty() && cross(Q[i].front(), i, j) > 0) {
        proceed(Q[i].front(), j);
        Q[i].pop_front();
    }
    // print("adding edge: {} -> {}\n", i, j);
    ++ans;

    Q[j].push_back(i);
}

int main() {
    PrimeSeq gen;
    for (int i = 1; i <= n; ++i) {
        int p1 = gen.next(), p2 = gen.next();
        x[i] += p1;
        y[i] += p1;
        x[i + 1] = x[i] + p2;
        y[i + 1] = y[i] - p2;
    }
    // for (int i = 1; i <= 10; ++i) {
    //     print("{} {}\n", x[i], y[i]);
    // }

    for (int i = 1; i <= n; ++i) {
        Q[i].clear();
    }
    for (int i = 1; i < n; ++i)
        proceed(i, i + 1);

    // long ans = 0;
    // for (int i = 1; i <= n; ++i)
        // ans += Q[i].size();
    print("ans = {}\n", ans);

    return 0;
}