#include "fmt/format.h"
#include <map>
using namespace fmt;
using namespace std;

const int n = 365, N = n + 2;
const int m = 7, LMT = 3;

map<pair<int, int>, double> f[N + m][N * LMT];
int state[m * 2 + 2];
double cb[N * LMT][LMT + 2];

void decode(int S, int *state) {
    for (int i = 0; i < m; ++i) {
        state[i] = (S >> (2 * i)) & 3;
    }
}

int encode(int *state) {
    int S = 0;
    for (int i = 0; i < m; ++i) {
        S |= state[i] << (2 * i);
    }
    return S;
}

int main() {
    f[0][0][{0, 0}] = 1;
    for (int i = 0; i <= n * LMT; ++i)
        for (int j = 0; j <= i && j <= LMT; ++j)
            cb[i][j] = j ? cb[i - 1][j - 1] / n + cb[i - 1][j] : 1;
    // for (int i = 0; i <= n * LMT; ++i) {
    //     for (int j = 0; j <= LMT; ++j) {
    //         print("{} ", cb[i][j]);
    //     }
    //     print("\n");
    // }

    for (int i = 0; i < n; ++i) {
        print("progress: {}\n", i);
        for (int j = 0; j <= i * LMT; ++j) {
            for (auto it : f[i][j]) {
                auto S = it.first.first;
                auto prob = it.second;

                decode(S, state + 1);
                int sum = 0;
                for (int t = 1; t <= m; ++t)
                    sum += state[t];
                int second = i == m ? S : it.first.second;

                for (int t = 0; t <= LMT - sum; ++t) {
                    state[0] = t;
                    auto s = encode(state);
                    f[i + 1][j + t][{s, second}] += prob * cb[j + t][t];
                    // print("trans: {}, {} {} => {}\n", i, j, S, s);
                }
            }
            f[i][j].clear();
        }
    }
    double ans = 0;
    for (int i = 0; i <= n * LMT; ++i) {
        for (auto it : f[n][i]) {
            decode(it.first.second, state);
            decode(it.first.first, state + m);

            int sum = 0;
            bool ok = true;
            for (int j = 0; j < 2 * m; ++j) {
                sum += state[j];
                if (j >= m + 1)
                    sum -= state[j - m - 1];
                if (sum > LMT)
                    ok = false;
            }
            if (ok)
                ans += it.second;
        }
        if (f[n][i].size())
            print("size: {}\n", f[n][i].size());
    }
    print("ans: {:0.12f}\n", ans);
    return 0;
}
