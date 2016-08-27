#include "fmt/format.h"
#include <NTL/ZZ.h>
#include "fmt/ostream.h"
#include <vector>
#include <map>
using namespace fmt;
using namespace NTL;
using namespace std;

map<long, vector<pair<long, long>>> generate(long L, long R) {
    map<long, vector<pair<long, long>>> ret;
    for (long a = 1, b_lb = SqrRoot(L); 2 * a * a <= L; ++a) {
        while (a * a + (b_lb - 1) * (b_lb - 1) >= L && b_lb > a)
            --b_lb;
        for (long b = b_lb; a * a + b * b <= R; ++b) {
            long s = a * a + b * b;
            ret[s].push_back({a, b});
        }
    }
    return ret;
}

int main() {
    const long S = 1e7;
    for (long i = 1; i <= 100; ++i) {
        auto f = generate((i - 1) * S + 1, i * S);

        int T = 0;
        for (auto a : f)
            T += a.second.size();
        print("{}\n", T);
    }
    return 0;
}