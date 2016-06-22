#include <cstdio>
#include <set>
using namespace std;

const int n = 3e6, N = n + 10, M = 20;

long U[N];

long power(long b, long e) {
    return e ? power(b, e - 1) * b : 1;
}

long B(long n) {
    return n ? B(n >> 1) + (n & 1) : 0;
}

double cur_max = 0;
long cur_peri = 0;
long o[10], len[M + 10];

void dfs(int dep, int choose) {
    if (dep == 0) {
        if (choose < 4)
            return;
        long s = 0;
        for (int i = 0; i < 4; ++i)
            s += o[i];
        double cur = 1;
        for (int i = 0; i < 4; ++i)
            cur *= s - o[i] * 2;
        if (cur > cur_max || (cur == cur_max && cur_peri < s)) {
            cur_max = cur;
            cur_peri = s;
            // printf("%ld %ld %ld %ld\n", o[0], o[1], o[2], o[3]);
        }
        return;
    }
    dfs(dep - 1, choose    );
    if (choose < 4 && len[dep] > 0)
        o[choose] = len[dep], dfs(dep - 1, choose + 1);
}

int main() {
    multiset<long> S;

    long ans = 0;
    for (int i = 1; i <= n; ++i) {
        U[i] = power(2, B(3 * i)) + power(3, B(2 * i)) + B(i + 1);
        if (S.count(U[i]) == 4) {
            ans += cur_peri;
            continue;
        }
        S.insert(U[i]);
        if (S.size() > M) {
            long removed = *S.begin();
            S.erase(S.begin());
            if (removed == U[i]) {
                ans += cur_peri;
                continue;
            }
        }

        printf("%d: U = %ld, acc = %ld\n", i, U[i], ans);
        auto it = S.rbegin();
        for (int x = 1; x <= M && it != S.rend(); ++x, ++it) {
            len[x] = *it;
            // if (i == 2621439) {
            //     printf("%ld, %d, %ld\n", len[x], (int) S.size(), *S.rbegin());
            // }
        }

        cur_max = 0, cur_peri = 0;
        dfs(M, 0);
        ans += cur_peri;
    }
    printf("%ld\n", ans);
    return 0;
}
