#include "fmt/format.h"
#include <NTL/ZZ.h>
#include <vector>
#include <set>
using namespace fmt;
using namespace NTL;
using namespace std;

const int N = 1e7, L = N;

vector<pair<int, int>> G[L];

int main() {
    int size = 0;
    for (int p = 1; p * p < L; ++p) {
        for (int q = 1; q < p && p * p + q * q <= L; ++q) {
            if (GCD(p, q) == 1 && (p % 2 != 1 || q % 2 != 1)) {
                int a = p * p - q * q;
                int b = 2 * p * q;
                int c = p * p + q * q;
                for (int t = 1; t * c <= L; ++t) {
                    if (a * t % 2 == 0)
                        G[a * t].push_back({b * t, c * t});
                    if (b * t % 2 == 0)
                        G[b * t].push_back({a * t, c * t});
                    size += 2;
                }
            }
        }
    }
    print("size = {}\n", size);

    int cnt = 0;
    long ans = 0;
    // b = AE, c = AB, a = sqrt(BC^2 - b^2 / 4)
    for (int b = 1; b <= L; b += 1) {
        set<int> S;
        for (auto x : G[b])
            S.insert(x.first);

        // print("{}\n", b);
        for (auto A : G[b]) {
            // if (b == 240)
            //     print("> {}\n", A.first);
            if (A.second % 2 != 0)
                continue;
            int a = A.first / 2;
            for (auto C : G[b]) {
                int c = C.first;
                // if (b == 240)
                //     print("> {} {}\n", A.first, c);
                if (c < a)
                    continue;

                if (S.count(a * 2 + 2 * c)) {
                    int peri = A.second + b + 2 * c;
                    if (peri <= N) {
                        ans += peri;
                        cnt += 1;
                        if (cnt % 100 == 1)
                            print("#{}: a = {} b = {} c = {}\n", cnt, a, b, c);
                    }
                }
            }
        }
    }
    print("ans = {}\n", ans);

    return 0;
}