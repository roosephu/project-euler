#include "fmt/format.h"
#include <NTL/ZZ.h>
#include <map>
#include <cassert>
using namespace fmt;
using namespace NTL;
using namespace std;

const long N = 1e13;
const int M = 1e7;

int primes[M / 10];
long ans = N;
int cnt = 0;
map<pair<int, long>, long> f;

long basis[M];
map<long, long> dvs;

long err(int depth, long val) {
    long p = primes[depth];
    if (p > val)
        return 1;
    if (p * p > val) {
        // assert(dvs.count(val) != 0);
        return dvs[val] - depth + 2;
    }
    if (depth % 30 != 0)
        return err(depth, val / primes[depth]) + err(depth + 1, val);

    auto S = make_pair(depth, val);
    if (!f.count(S)) {

        f[S] = err(depth, val / primes[depth]) + err(depth + 1, val);
    }
    return f[S];
}

void dfs(int depth, long val, long e) {
    for (int i = depth + 1; i <= primes[0]; ++i) {
        long p = primes[i];
        long v = val;
        if (p * p > val)
            break;
        for (int t = 1; (v /= p) > 0; ++t) {
            if (t > e) {
                cnt += 1;
                if (cnt % 1000000 == 0)
                    print("#{}: |map| = {}, depth = {}, val = {}\n", cnt, f.size(), i, v);
                ans -= err(i, v);
                break;
            } else {
                if (p * p <= v)
                    dfs(i, v, t);
            }
        }
    }
}

void init_num_primes(long n) {
    long R = SqrRoot(n);
    int cnt = 0;
    for (long i = 1; n / i > R; ++i)
        basis[++cnt] = n / i;
    for (int i = R; i; --i)
        basis[++cnt] = i;

    for (int i = 1; i <= cnt; ++i) {
        long x = basis[i];
        dvs[x] = x - 1;
    }
    for (long x = 2; x <= R; ++x) {
        if (ProbPrime(x)) {
            print("current x: {}\n", x);
            for (int i = 1; i <= cnt; ++i) {
                long y = basis[i];
                if (x * x > y)
                    break;
                auto a = dvs[y / x];
                auto b = dvs[x - 1];
                dvs[y] -= a - b;
            }
        }
    }
    print("num primes initialized...\n");
}

int main() {
    PrimeSeq gen;
    for (long v; v = gen.next(), v <= M; )
        primes[++primes[0]] = v;
    print("#primes = {}\n", primes[0]);
    init_num_primes(N);

    dfs(0, N, 100);
    print("ans = {}\n", ans);
    print("|map| = {}\n", f.size());

    return 0;
}