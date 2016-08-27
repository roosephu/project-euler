#include "fmt/format.h"
#include "fmt/ostream.h"
#include <NTL/mat_lzz_p.h>
#include <map>
using namespace fmt;
using namespace NTL;
using namespace std;

const long m = 2 * 10, n = 1e12, MOD = 1e9, M = (m + 2) * (m + 1);

map<int, int> f;
zz_p cb[m + 1][m + 1];

int get_state(int a, int b, int c, int t) {
    int S = ((a * m + b) * m + c) * 2 + t;
    if (f.count(S) == 0) {
        int x = f.size();
        f[S] = x;
        // print("a = {}, b = {}, c = {}, t = {} => {}\n", a, b, c, t, x);
    }
    return f[S];
}

int main() {
    zz_p::init(MOD);

    Mat<zz_p> G;
    G.SetDims(M, M);
    for (int i = 0; i <= m; ++i)
        for (int j = 0; j <= i; ++j)
            cb[i][j] = j ? cb[i - 1][j - 1] + cb[i - 1][j] : zz_p(1);

    for (int a = 0; a <= m; ++a) {
        for (int b = 0; a + b <= m; ++b) {
            int c = m - a - b;
            for (int t = 0; t < 2; ++t) {
                int S = get_state(a, b, c, t);
                for (int da = 0; da <= a; ++da) {
                    for (int db = 0; db <= b; ++db) {
                        int T = 0;
                        if (da + db + c == 0) {
                            if (t == 0) {
                                T = get_state(0, a, b, 1);
                            } else {
                                continue;
                            }
                        } else {
                            T = get_state(da + db + c, a - da, b - db, t);
                        }
                        G[T][S] += cb[a][da] * cb[b][db];
                    }
                }
            }
        }
    }
    power(G, G, n - 1);

    // print("G = {}\n", G);

    print("ans = {}\n", G[get_state(m, 0, 0, 0)][get_state(m, 0, 0, 0)] + G[get_state(m, 0, 0, 1)][get_state(m, 0, 0, 0)]);

    return 0;
}