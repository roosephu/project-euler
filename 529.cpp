#include <cstdio>
#include <map>
using namespace std;

const int m = 10, M = 256 * 11 + 2, MOD = 1000000007;
const long n = 1e18;
typedef long mat[M][M];

map<pair<int, int>, int> f;
int D;

mat A, B, t, x;

int get(int S, int t) {
    if (!f.count({S, t}))
        f[{S, t}] = f.size();
    return f[{S, t}];
}

void matmul(mat A, mat B, mat C) {
    for (int i = 0; i < D; ++i)
        for (int j = 0; j < D; ++j)
            x[i][j] = B[j][i];
    for (int i = 0; i < D; ++i)
        for (int j = 0; j < D; ++j)
            t[i][j] = 0;
    for (int i = 0; i < D; ++i) {
        if (i % 100 == 0)
            printf("%d\n", i);
        for (int j = 0; j < D; ++j)
            for (int k = 0; k < D; ++k)
                if (A[i][k] && x[j][k])
                    (t[i][j] += A[i][k] * x[j][k]) %= MOD;
    }
    for (int i = 0; i < D; ++i)
        for (int j = 0; j < D; ++j)
            C[i][j] = t[i][j];
}

int main() {
    for (int S = 0; S < (1 << m); S += 2) {
        for (int x = 0; x < m; ++x) {
            if ((S | 1) >> x & 1) {
                for (int i = 0; i < m; ++i) {
                    int uncovered = S & ((1 << (x + 1)) - 1), t = x + i;
                    if (S >> (m - i) & 1) {
                        uncovered &= ~(1 << (m - i));
                        t = 0;
                    }

                    if ((uncovered >> (m - i)) == 0) {
                        int s = (S << i);
                        if (i != 0)
                            s |= 1 << i;
                        s &= ((1 << m) - 1);

                        A[get(s, t)][get(S, x)] += 1;
                    }
                }
            }
        }
    }

    D = f.size();
    for (int i = 0; i < D; ++i)
        B[i][i] = 1;
    for (long e = n; e; e >>= 1, matmul(A, A, A))
        e & 1 ? matmul(A, B, B), 0 : 0;

    long ans = 0;
    for (int S = 0; S < (1 << m); S += 2)
        ans += B[get(S, 0)][get(0, 0)];
    printf("ans = %ld\n", ans % MOD);

    return 0;
}
