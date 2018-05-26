#include "lib.h"

namespace PE483 {
    const int n = 350, maxN = 400;
    typedef long double LD;

    LD logX[maxN];
    LD logFac[maxN];
    int S[maxN];
    int nodes;
    int cycleCnt[maxN], gcds[maxN];
    LD logProb, logPeriod;
    LD ans;

    const int m = 5, maxT = 2592, primes[] = {2, 3, 5, 7, 11, 13, 17}, powers[] = {9, 6, 4, 4, 3, 3, 3};
    LD f[maxT][maxN], g[maxT][maxN];
    int head[maxN], tail[maxN], weights[maxN][m];

    void addItem(int x) {
        if (cycleCnt[x] == 0) {
            int d = gcds[0] + 1;
            gcds[0] = d;

            gcds[d] = head[x];
            for (int i = 1; i < d; ++i) {
                int y = gcds[i];
                gcds[d] /= GCD(gcds[d], y);
            }
            logPeriod += logX[gcds[d]];
        }
        cycleCnt[x] += 1;
        logProb += logX[x] + logX[cycleCnt[x]];
    }

    void removeItem(int x) {
        logProb -= logX[x] + logX[cycleCnt[x]];
        cycleCnt[x] -= 1;
        if (cycleCnt[x] == 0) {
            int d = gcds[0];

            logPeriod -= logX[gcds[d]];
            gcds[0] -= 1;
        }
    }

    void decode(int x, int *out) {
        for (int j = 0; j < m; ++j) {
            out[j] = x % powers[j];
            x /= powers[j];
        }
    }

    int encode(int *in) {
        int z = 0;
        for (int j = m - 1; j >= 0; --j) {
            z = z * powers[j] + in[j];
        }
        return z;
    }

    int add(long x, long y) {
        int xs[m], ys[m];
        decode(x, xs);
        decode(y, ys);
        for (int i = 0; i < m; ++i) {
            xs[i] = max(xs[i], ys[i]);
        }
        return encode(xs);
    }

    void dfs(int n, int t, int state) {
        ans += exp(logPeriod * 2 - logProb) * g[state][n];
        t = min(t, n);
        for (int i = t; i; --i) {
            if (head[i] != 1) {
                addItem(i);
                dfs(n - i, i, add(state, tail[i]));
                removeItem(i);
            }
        }
    }

    void main() {
        for (int i = 1; i <= n; ++i) {
            logX[i] = log(i);
            logFac[i] = logFac[i - 1] + logX[i];
        }
        for (int i = 1; i <= n; ++i) {
            int x = i;
            for (int j = 0; j < m; ++j) {
                while (x % primes[j] == 0) {
                    ++weights[i][j];
                    x /= primes[j];
                }
            }
            head[i] = x;
            tail[i] = encode(weights[i]);
        }

        print("dp...\n");
        f[0][0] = 1;
        for (int i = n; i; --i) {
            if (head[i] != 1) continue;
            // print("{} {}\n", i, tail[i]);
            for (int t = maxT - 1; t >= 0; --t) {
                int t_ = add(t, tail[i]);
                // print("{} {} => {}\n", t, tail[i], t_);
                for (int s = n; s >= i; --s) {
                    for (int c = 1; c * i <= s; ++c) {
                        LD prob = exp(c * logX[i] + logFac[c]);
                        f[t_][s] += f[t][s - c * i] / prob;
                    }
                }
            }
        }
        print("pre...\n");
        for (int x = 0; x < maxT; ++x) {
            int xs[m], ys[m];
            decode(x, xs);
            // if (x % 1000 == 0) {
            //     print("{}\n", x);
            // }
            for (int y = 0; y < maxT; ++y) {
                decode(y, ys);
                LD value = 0;
                for (int i = 0; i < m; ++i) {
                    value += logX[primes[i]] * max(xs[i], ys[i]);
                }
                value = exp(value * 2);
                for (int i = 0; i <= n; ++i) {
                    g[y][i] += f[x][i] * value;
                }
            }
        }

        print("dfs...\n");
        dfs(n, n, 0);
        print("ans = {:.9e}\n", ans);
        // for (int i = 0; i < 54; ++i) {
        //     print("{} {} {} {}\n", f[i][0], f[i][1], f[i][2], f[i][3]);
        // }
    }
}

int main() {
    PE483::main();
    return 0;
}
