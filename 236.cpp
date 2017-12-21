#include "fmt/format.h"
#include <NTL/ZZ.h>
#include <set>
using namespace fmt;
using namespace NTL;
using namespace std;

namespace PE236 {
    bool is_sqr(int x) {
        int t = SqrRoot(x);
        return x == t * t;
    }

    void main() {
        int cnt = 0;
        set<pair<int, int>> S;
        for (long b = 5; b <= 640; b += 5) {
            for (long t = 1; t <= 11328; t += 1) {
                // if ((59 * b / 5 + t) % 5 != 0) continue;
                for (long h = 41; h <= 3776; h += 41) {
                    long A = 6 * ((59 * b + t * 5) * 41 + 450 * h);
                    long B = (b + t + h) * 41 * 25;
                    long g = GCD(A, B);
                    B /= g, A /= g;
                    if ((59. / 41) * (59. / 41) * B / A > 1.) continue;
                    if (is_sqr(A) && is_sqr(B)) {
                        A = SqrRoot(A), B = SqrRoot(B);
                        if (b * 59 * B % (A * 5) != 0) continue;
                        if (t % A != 0) continue;
                        if (h * 90 * B % (A * 41) != 0) continue;
                        pair<int, int> s = {B, A};
                        if (!S.count(s)) {
                            S.insert(s);
                            ++cnt;
                            print("#{}: b = {}, t = {}, h = {}, m = {}/{}, ans = {}\n", cnt, b, t, h, B * 59, A * 41, B * 59. / (A * 41.));
                        }
                    }
                }
            }
        }
        if (S.count({25, 36}))
            print("good!\n");
    }
}

int main() {
    PE236::main();
    return 0;
}
