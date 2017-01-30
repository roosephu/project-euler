#include "fmt/format.h"
#include "fmt/ostream.h"
#include <NTL/ZZ.h>
#include <algorithm>
using namespace fmt;
using namespace NTL;
using namespace std;

const int n = 10000, N = 10000;

int cnt, p, top;
int primes[N];
ZZ prod, opt;
ZZ coef[1000];
ZZ buf[1 << 20];

void dfs(int L, int R, ZZ val) {
    if (L > R) {
        val %= prod;
        if (R != cnt) {
            buf[top] = val;
            ++top;
            // print("| p = {}, val = {}\n", p, val);
        } else {
            ZZ v = (val + *lower_bound(buf, buf + top, (prod + p + 1 - val) % prod)) % prod;
            if (v < p)
                v += prod;
            // print("- p = {}, val = {}, v = {}\n", p, val, v);
            if (opt == 0 || opt > v)
                opt = v;
        }
        return;
    }
    dfs(L + 1, R, val              );
    dfs(L + 1, R, val + coef[L] * p);
}

int main() {
    PrimeSeq gen;
    for (int i = 1; i <= 1000; ++i) {
        primes[i] = gen.next();
    }

    ZZ ans{0};
    for (int i = 1; primes[i] <= n; ++i) {
        p = primes[i];

        prod = 1;
        cnt = 0;
        for (int j = 1; primes[j] * primes[j] <= p; ++j) {
            cnt += 1;
            prod *= primes[j];
        }

        opt = 0;
        if (prod <= p * p) {
            for (int A = p / 2; A < p; ++A) {
                int B = p - A;
                if (A < B)
                    continue;
                if (ZZ(A * B) % prod == 0) {
                    if (opt == 0 || A <= opt)
                        opt = A;
                }
            }
        }

        if (cnt >= 3) {
            for (int j = 1; j <= cnt; ++j)
                coef[j] = InvMod(prod / primes[j] % primes[j], primes[j]) * prod / primes[j];

            top = 0;
            dfs(1, cnt / 2, ZZ(0));
            sort(buf, buf + top);
            buf[top] = buf[0];

            dfs(cnt / 2 + 1, cnt, ZZ(0));

            print("{}: cnt = {}, opt = {}, prod = {}\n", p, cnt, opt, prod);
        }

        ans += opt;
    }
    print("ans = {}\n", ans);

    return 0;
}