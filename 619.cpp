#include "fmt/format.h"
#include <vector>
#include <NTL/ZZ.h>
using namespace fmt;
using namespace std;
using namespace NTL;

namespace PE619 {

    const long L = 1000000, R = 1234567;
    const int MOD = 1e9 + 7;

    typedef vector<int> Row;

    int complexity;
    Row xs[R];
    int idx[R];
    int n;

    Row merge(const Row &a, const Row &b) {
        complexity += a.size() + b.size();
        Row ret;
        auto p = a.begin(), q = b.begin();
        while (q != b.end()) {
            while (p != a.end() && *p < *q) {
                ret.push_back(*p);
                ++p;
            }
            if (p != a.end() && *p == *q) {
                ++p;
                ++q;
            } else {
                ret.push_back(*q);
                ++q;
            }
        }
        while (p != a.end()) {
            ret.push_back(*p);
            ++p;
        }
        return ret;
    }

    int get_e(int n, int p) {
        int e = 0;
        while (n % p == 0) {
            ++e;
            n /= p;
        }
        return e;
    }

    void add(Row x) {
        while (!x.empty()) {
            int t = x[0];
            if (xs[t].empty()) {
                ++n;
                xs[t] = x;
                break;
            } else {
                x = merge(x, xs[t]);
            }
        }
    }

    void main() {
        n = 0;

        PrimeSeq gen;
        for (int p; (p = gen.next()) <= R; ) {
            long l = (L - 1) / p + 1;
            long r = R / p;
            Row x;
            for (int i = l; i <= r; ++i) {
                if (get_e(i * p, p) % 2 != 0) {
                    x.push_back(i * p);
                }
            }
            // for (auto t : x) {
            //     print("{} ", t);
            // }
            // print("\n");

            add(x);
        }

        print("complexity = {}\n", complexity);
        print("ans = {}\n", PowerMod(2, R - L + 1 - n, MOD) - 1);
    }
}

int main() {
    PE619::main();
    return 0;
}
