#include "fmt/format.h"
using namespace fmt;

const int T = 12;

int cnt = 0;
long ans = 0;

bool check(long v, int b) {
    long S = 0;
    for (; v; v /= b)
        S |= 1 << (v % b);
    return S == ((1 << b) - 1);
}

void dfs(int S, long v) {
    if (S == 0) {
        for (int i = T - 1; i >= 2; --i)
            if (!check(v, i))
                return;
        cnt += 1;
        ans += v;
        print("#{} = {}, sum = {}\n", cnt, v, ans);
        return;
    }
    for (int i = 0; i < T; ++i)
        if (S >> i & 1) {
            if (S != (1 << T) - 1 || i != 0)
                dfs(S ^ (1 << i), v * T + i);
        }
}

int main() {

    dfs((1 << T) - 1, 0);
    return 0;
}