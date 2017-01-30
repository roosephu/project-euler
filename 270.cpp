#include "fmt/format.h"
#include "fmt/ostream.h"
#include <map>
#include <NTL/ZZ.h>
using namespace fmt;
using namespace std;
using namespace NTL;

const int MOD = 1000000087, M = 128, N = 33;

long inv[M];
map<long, ZZ> f;
int cnt = 0, ptr = 0;

void preprocess(int *v, int n, long *buf) {
    // if (n == 7)
    //     print("{} {}\n", i, j);

    int last = -1, cnt = 0;
    long ret = 0;
    for (int i = 0; i < n; ++i) {
        if (last != v[i]) {
            last = v[i];
            ret = ret << 8 | cnt;
            cnt = 0;
        }
        ++cnt;
        last = v[i];
        buf[i] = ret << 16 | cnt << 8 | 1;
    }
}

long min_rep(long S) {
    long ret = S, T = S;
    int u[10], n = 0;
    for (; S; ++n) {
        u[n] = S & 0xff;
        S >>= 8;
    }

    for (int i = 0; i < n; ++i) {
        ret = min(ret, T);
        T = (long) u[i] << (8 * (n - 1)) | T >> 8;
    }
    return ret;
}

ZZ dp(long S) {
    if (S == 0x10101) return ZZ(1);
    S = min_rep(S);

    long T = S;
    if (!f.count(S)) {
        int v[M * 2], u[M * 2];
        long bv[M], bu[M];
        int offset = 0;
        for (int i = 0; T; ++i) {
            int t = T & 0xff;
            for (int j = 0; j < t; ++j) {
                v[offset++] = i;
                // print("{} ", i);
            }
            T = T >> 8;
        }
        for (int i = 0; i < offset; ++i)
            v[offset + i] = v[i];
        for (int i = 0; i < offset * 2; ++i)
            u[offset * 2 - 1 - i] = v[i];

        ZZ ans{0};
        for (int i = 0; i < offset; ++i) {
            preprocess(v + i, offset, bv);
            preprocess(u + (offset - i) % offset, offset, bu);

            for (int j = i + 1; j < offset; ++j) {
                if (v[i] != v[j] && j - i <= offset - 1) {
                    // long X = encode(v, i, j, offset);
                    // long Y = encode(v, j, i, offset);
                    long X = bv[j - i - 1];
                    long Y = bu[offset - 1 - (j - i)];
                    if (X < 0x10000 || Y < 0x10000)
                        continue;
                    // print("{:x} ({}, {}) => {:x} {:x}\n", S, i, j, X, Y);
                    ans += dp(X) * dp(Y);
                }
            }
        }

        if (cnt % 1000 == 0) {
            print("{:x}: {} offset = {}\n", S, ans, offset);
            assert(ans % (offset - 3) == 0);
        }
        ++cnt;
        f[S] = ans / (offset - 3);
    }
    return f[S];
}

int main() {
    // inv[1] = 1;
    // for (int i = 2; i < M; ++i) {
    //     inv[i] = (long) (MOD / i) * (MOD - inv[MOD % i]) % MOD;
    //     // print("{}\n", i * inv[i] % MOD);
    // }

    long n = 30;
    // print("{:x}\n", min_rep(1ll << 0 | 2ll << 8 | 3ll << 16));
    print("ans = {}\n", dp(n << 0 | n << 8 | n << 16 | n << 24));
    return 0;
}

// 1000000007: 938106376
// 1000000009: 253059321
// 1000000021: 43879285
// 1000000033: 136731062
// 1000000087:
// 1000000093:
// 1000000097:
// 1000000103:
// 1000000123:
// 1000000181:
