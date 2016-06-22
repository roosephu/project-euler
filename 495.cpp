#include <cstdio>
#include <NTL/lzz_p.h>
#include <NTL/ZZ.h>
#include <map>
#include <vector>
using namespace std;
using namespace NTL;

const int MOD = 1e9 + 7, n = 1e4, N = n + 10, m = 30, M = m + 3, PN = 6000;

int dim = 0;
int val[N];
vector<zz_p> dp[M][N];
map<vector<int>, int> ids;
vector<int> stack, states[PN];
zz_p f[PN];
zz_p g[M][M * M / 2], fac[M * M], caf[M * M];
zz_p w[M], ans;

zz_p cb(int n, int m) {
    if (n < m) return zz_p(0);
    return fac[n] * caf[m] * caf[n - m];
}

void dfs(int dep, int rem, int last) {
    if (rem == 0) {
        vector<int> v(stack);
        int id = ids.size() + 1;
        // if (id % 100 == 0)
        //     printf("%d\n", id);
        states[id] = v;
        ids[v] = id;
        zz_p cnt(1), c(1);
        for (int i = 1; i <= dim; ++i) {
            c *= dp[dep][i][val[i]];
        }

        int rem_size = m, last = 0, t = 0;
        for (auto x : stack) {
            cnt *= cb(rem_size, x) * w[x];
            rem_size -= x;
            if (x == last)
                ++t;
            else
                t = 1;
            last = x;

            cnt /= t;
            // printf("%d ", x);
        }

        f[id] = cnt;
        ans += cnt * c;
        // printf(": cnt = %ld, c = %ld\n", rep(cnt), rep(c));
        return;
    }
    ++dep;
    if (last > rem) last = rem;
    for (; last; --last) {
        stack.push_back(last);

        for (int i = 1; i <= dim; ++i) {
            for (int j = 0; j <= val[i]; ++j) {
                dp[dep][i][j] = dp[dep - 1][i][j];
                if (j >= last)
                    dp[dep][i][j] += dp[dep][i][j - last];
            }
        }

        dfs(dep, rem - last, last);
        stack.pop_back();
    }
}

int main() {
    zz_p::init(MOD);

    fac[0] = 1;
    int L = m * (m - 1) / 2;
    for (int i = 1; i <= L; ++i)
        fac[i] = fac[i - 1] * i;
    caf[L] = 1 / fac[L];
    for (int i = L; i >= 1; --i)
        caf[i - 1] = caf[i] * i;

    // printf("%ld\n", rep(fac[4]));
    g[0][0] = 1;
    for (int i = 1; i <= m; ++i)
        for (int j = 0; j <= i * (i - 1) / 2; ++j) {
            g[i][j] = cb(i * (i - 1) / 2, j);
            for (int x = 1; x < i; ++x) {
                for (int y = 0; y <= x * (x - 1) / 2 && y <= j; ++y) {
                    g[i][j] -= g[x][y] * cb(i - 1, x - 1) * cb((i - x) * (i - x - 1) / 2, j - y);
                }
            }
        }
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= i * (i - 1) / 2; ++j)
            if (j % 2 == 0)
                w[i] += g[i][j];
            else
                w[i] -= g[i][j];
        printf("%d: %ld, %d\n", i, rep(w[i]), rep((i > 0 ? fac[i - 1] : zz_p(1)) * (i % 2 == 0 ? -1 : 1)));
    }

    for (int i = 2; i <= n; ++i) {
        if (ProbPrime(i)) {
            ++dim;
            for (int j = n; j /= i; )
                val[dim] += j;
        }
    }
    // dim = 2;
    // val[1] = 4, val[2] = 2;
    for (int i = 1; i <= dim; ++i) {
        for (int d = 0; d <= m; ++d)
            dp[d][i].resize(val[i] + 1);
        dp[0][i][0] = 1;
    }

    dfs(0, m, m);

    ans = ans * caf[m];

    printf("%ld\n", rep(ans));
    return 0;
}
