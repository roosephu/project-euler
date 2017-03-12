#include <map>
using namespace std;

map<long, long> M;

long Mertens(long n) {
    if (n == 1)
        return 1;
    if (!M.count(n)) {
        long ret = 1;
        for (long i = 2; i <= n; ) {
            long j = n / (n / i) + 1;
            ret -= (j - i) * Mertens(n / i);
            i = j;
        }
        M[n] = ret;
    }
    return M[n];
}