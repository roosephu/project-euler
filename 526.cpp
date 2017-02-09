#include "fmt/format.h"
#include <vector>
#include <NTL/ZZ.h>
#include <cstdlib>
using namespace fmt;
using namespace NTL;
using namespace std;

const int MAX_PRIMES = 10000000;
const int LMT = 1e8;
const long N = 1e16;

int primes[MAX_PRIMES];
long dvs[9] = {1, 6, 1, 2, 15, 2, 1, 6, 1};
int inv[100][100];
long ans = 49166660662415341ll;
// double rate = 4.916;

void dfs(int depth, long lcm, long val) {
    if (depth == 12) {
        print("lcm = {}, val = {}\n", lcm, val);
        // exit(0);
        // if (!ProbPrime(val) || !ProbPrime(val + 2) || !ProbPrime)
        return;
    }
    int p = primes[depth];

    vector<pair<double, int>> vec;
    for (int i = 0; i < p; ++i) {
        double cur = 0;
        for (int t = 0; t < 9; ++t) {
            if ((t + i) % p == 0) {
                cur += 1. / dvs[t] / p;
            } else {
                cur += 1. / dvs[t];
            }
        }

        vec.push_back({-cur, i});
    }

    sort(vec.begin(), vec.end());
    long mul = inv[p][lcm % p];
    for (auto it : vec) {
        int rem = it.second, start = rem ? p - rem : 0;
        long new_lcm = lcm * p, new_val = val + lcm * (rem * mul % p);
        if ((N / new_lcm * new_lcm + new_val) * -it.first < ans)
            continue;
        for (int i = start; i < 9; i += p)
            dvs[i] *= p;
        if (it.first == vec[0].first)
            dfs(depth + 1, new_lcm, new_val);
        for (int i = start; i < 9; i += p)
            dvs[i] /= p;
    }
}

int main() {
    PrimeSeq gen;
    for (int u; (u = gen.next()) < LMT; )
        primes[++primes[0]] = u;
    for (int i = 1; i < 100; ++i) {
        inv[i][1] = 1;
        for (int j = 2; j < i; ++j)
            inv[i][j] = (i / j) * (i - inv[i][i % j]) % i;
    }
    dfs(4, 30, 11);
    return 0;
}