#include "fmt/format.h"
#include <vector>
#include <map>
using namespace fmt;
using namespace std;

const int n = 16;

int lb[] = {0, -72, -3, -1, 0, 0, 0, 0, 0, 0};
int rb[] = {9,  72,  6,  3, 2, 1, 1, 1, 1, 1};

long dp(int state) {
    map<vector<int>, long> f, g;
    vector<int> zeros;
    for (int i = 0; i < 10; ++i)
        if (state >> i & 1)
            zeros.push_back(0);
    f[zeros] = 1;

    for (int _ = 0; _ < n; ++_) {
        // print("-------\n");
        for (auto &it : f) {
            // for (int i = 0; i <= 9; ++i)
            //     if (state >> i & 1)
            //         print("{} ", it.first[i]);
            // print(": {}\n", it.second);
            for (int d = 0; d <= 9; ++d) { // digits
                vector<int> S;
                bool ok = true;
                for (int b = 0, idx = 0; b <= 9; ++b) {
                    if (state >> b & 1) {
                        int v = d - it.first[idx] * b;
                        if (v < lb[b] || v > rb[b]) {
                            ok = false;
                            break;
                        }
                        S.push_back(v);
                        ++idx;
                    }
                }
                if (ok) {
                    g[S] += it.second;
                }
            }
        }
        f = g;
        g.clear();
    }

    long ret = 0;
    for (auto &it : f) {
        bool ok = true;
        for (auto v : it.first) {
            if (v != 0) {
                ok = false;
                break;
            }
        }
        if (ok)
            ret += it.second;
    }
    return ret;
}

int parity(int x) {
    int ret = 0;
    for (; x; x >>= 1)
        ret ^= x & 1;
    return ret;
}

int main() {
    long ans = 0;
    for (int S = 1; S < (1 << 10); ++S) {
        long delta = dp(S);
        // print("{}: {}\n", S, delta);
        // ans += dp(S);
        ans += parity(S) ? delta : -delta;
    }
    print("ans = {}\n", ans);
    return 0;
}