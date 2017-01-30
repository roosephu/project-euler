
long basis[M];
map<long, long> dvs;

void init_num_primes(int n) {
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
}
