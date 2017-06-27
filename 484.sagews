︠c90c05e5-7b8b-4bca-95b7-5ebff9425a46︠
%cython

import sage.all as _
ctypedef long long int64

cdef int64 N = 5 * 10**15
cdef int64 primes[5000000], LMT = 71000000, top
cdef int64 up[5000000]
cdef int64 ans = 0

P = _.primes(LMT)
for p in P :
    top += 1
    primes[top] = p
    up[top] = N / p / p

cdef int64 f(int64 x, int e, int p) :
    if e % p == 0 :
        return x
    return x / p

cdef dfs(int d, int64 cur, int64 g) :
    if g == 0 :
        return 
    print cur, g
    global ans
    
    cdef int i, p, e
    cdef int64 t, x, S = N / cur

    ans += S * g
    for i in range(d + 1, top) :
        if up[i] < cur :
            break
        p = primes[i]
        e = 0
        x = 1
        while x * p <= S :
            x *= p
            e += 1
            if e >= 2 :
                dfs(i, cur * x, g * (f(x, e, p) - f(x / p, e - 1, p)))

dfs(0, 1, 1)

print ans

︡cd8b1843-6a7d-463f-9584-f739d3c2cb13︡
︠894fc163-3308-44bb-bea2-922c5a35324b︠
︡060963d6-b262-41ee-96ff-9830f2b421d0︡
︠f33fa7ce-a40d-4b03-962a-3f91b9b14657︠









