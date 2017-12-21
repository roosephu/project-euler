#include "fmt/format.h"
#include <set>
#include <NTL/ZZ.h>
#include <cmath>
using namespace std;
using namespace fmt;
using namespace NTL;

namespace PE615 {
    struct node {
        double v;
        int last;
        node *prev;

        node(double v_, int last_, node *prev_) : v(v_), last(last_), prev(prev_) {}
    };

    const int n = 1e6, N = n + 10, MOD = 123454321;

    int primes[N];
    double log_p[N];

    struct cmp {
        bool operator () (node *a, node *b) {
            return a->v < b->v;
        }
    };

    void main() {
        PrimeSeq gen;
        for (int i = 1; i <= n; ++i) {
            primes[i] = gen.next();
            log_p[i] = log(primes[i]);
        }

        int newed = 0;
        set<node*, cmp> S;
        for (int i = n; i < n * 2; ++i) {
            S.insert(new node(log_p[1] * i, 2, nullptr));
            newed++;
        }
        double limit = (*S.rbegin())->v;

        for (int i = 1; i < n; ++i) {
            node *x = *S.begin(); S.erase(S.begin());

            for (int t = x->last; t <= n; ++t) {
                double v = x->v + log_p[t] - log_p[1];
                if (v > limit) break;
                S.insert(new node(v, t, x));
                ++newed;
            }

            while (S.size() > n - i) {
                node *y = *S.rbegin();
                delete y;
                S.erase(--S.end());
            }
            limit = (*S.rbegin())->v;
        }
        node *x = *S.begin();
        print("log: {}\n", x->v);

        long ans = 1;
        for (int t = 0; ; x = x->prev, ++t) {
            if (x->prev) {
                ans = ans * primes[x->last] % MOD;
                print("{}\n", primes[x->last]);
            } else {
                int n2 = x->v / log_p[1] + 0.5 - t;
                print("#2 = {}\n", n2);
                ans = ans * PowerMod(2, n2, MOD) % MOD;
                break;
            }
        }

        print("ans = {}, newed = {}\n", ans, newed);
    }
}

int main() {
    PE615::main();
    return 0;
}
