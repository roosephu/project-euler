#include <cstdio>
#include <set>
using namespace std;

const int N = 5;

set<int> S;

void dfs(int d, long n, int seq, int last) {
    if ((n & (n - 1)) == 0 && d != N)
        return;
    if (d == 0) {
        if (S.count(seq) == 0) {
            S.insert(seq);
            printf("found: %20ld, ", n);
            for (int i = 0; i < N; ++i) {
                if (n % 2 == 0) {
                    printf("0");
                    n /= 2;
                } else {
                    printf("1");
                    n = n * 3 + 1;
                }
            }
            printf("\n");
        }
        return;
    }

    if (n % 3 == 1 && n % 2 == 0)
        dfs(d - 1, (n - 1) / 3, seq << 1 | 1, 1);
    dfs(d - 1, 2 * n, seq << 1 | 0, 0);
}

int main() {
    for (int i = 1; i <= 40; ++i)
        dfs(N, 1l << i, 0, 0);
    printf("%d\n", (int) S.size());
    return 0;
}
