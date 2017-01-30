#include <cstdio>
#include <algorithm>
#include <cassert>
#include <NTL/ZZ.h>
using namespace std;
using namespace NTL;

const long L = 8916100448256ll;

int perm[100];
bool used[100];

long count_perm(int *perm, int n) {
    long ret = 0;
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        // assert(1 <= perm[i] && perm[i] <= n);
        if (perm[i] > mx) {
            mx = perm[i];
        } else {
            int cnt = 0;
            for (int j = 1; j < i; ++j)
                if (perm[j] < perm[i])
                    ++cnt;
            ret += 1ll << cnt;
        }
    }
    return ret;
}

bool is_possible(int *prefix, int n, int finished, long rank) {
    long lb = 0, ub = 0;
    int cur_max = 0;
    for (int i = 1; i <= finished; ++i) {
        cur_max = max(cur_max, prefix[i]);
    }

    // lower bound
    for (int pos = finished + 1, x = max(cur_max - 1, 0), y = cur_max + 1; pos <= n; ++pos) {
        while (x > 0 && used[x])
            --x;
        if (x == 0) {
            while (used[y])
                ++y;
            prefix[pos] = y;
            y += 1;
        } else {
            prefix[pos] = x;
            x -= 1;
        }
    }
    lb = count_perm(prefix, n);

    // upper bound
    int ub_pos = finished + 1;
    if (!used[n]) {
        prefix[ub_pos] = n;
        ub_pos += 1;
    }
    for (int pos = ub_pos, x = 1, y = n; pos <= n; ++pos) {
        while (used[x])
            ++x;
        prefix[pos] = x;
        x += 1;
    }
    ub = count_perm(prefix, n);
    // printf("%lld %lld %lld\n", lb, ub, rank);

    return lb <= rank && rank <= ub;
}

void dfs(int n, int dep) {
    // printf("dep: %d ", dep);
    long current = L - count_perm(perm, dep - 1);
    if (weight(cnt) > (n - dep + 1)) {
        printf("cut bin @ %d: %d %d\n", dep, weight(cnt), n - dep + 1);
        return;
    }
    if (dep > n) {
        for (int i = 1; i <= n; ++i) {
            printf("%d\n", perm[i]);
        }
        return;
    }

    int min_pos = 1;
    for (; used[min_pos]; )
        ++min_pos;
    if (current & ((1ll << (min_pos - 1)) - 1)) {
        return;
    }

    if (!is_possible(perm, n, dep - 1, L)) {
        if (dep < 35)
            printf("cut @ %d\n", dep);
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (used[i])
            continue;
        used[i] = true;
        perm[dep] = i;
        dfs(n, dep + 1);
        used[i] = false;
    }
}

int main() {
    dfs(45, 1);
    return 0;
}
