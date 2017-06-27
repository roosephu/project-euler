︠ddf84898-93ca-4e4e-a9b4-7feb07e759dfsr︠
%cython
#clang C++

ctypedef long long int64

cdef int N = int(1e3)

cdef int lnk[11000], primes[11000]

cdef void sieve(int n):
    cdef int k = 0, t, i
    for i from 2 <= i <= n:
        if primes[i] == 0:
            k = primes[0] + 1
            primes[k] = i
            primes[0] = k
            lnk[i] = i
        k = n / i
        for j from 1 <= j <= primes[0]:
            t = primes[j] * i
            primes[t] = 0
            lnk[t] = i
            if i % primes[j] == 0:
                break

sieve(N + 1)
cdef int i, top = 0
cdef int val[100], exp[100]

for i from 1 <= i <= primes[0]:
    # factor (i + 1)^2
    top = 0
    u = i + 1
    while u != 1:
        x = lnk[u]
        top += 1
        val[top] = x
        while x == lnk[u]:
            exp[top] += 2
            u /= x
        print i, val[top], exp[top]
︡cd853be4-fd6c-4a6e-93d3-375b518adebc︡
︠6cb884bd-c457-466f-8250-dc0e1c2a926e︠
︡b604b3c6-a3c7-439a-8734-322644e39898︡
︠8797f798-fda5-43a2-84f9-0697c7926f52︠









