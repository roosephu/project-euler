p = list(primes(20))
oa, ob = 0, 1

for i in range(len(p)):
    na = CRT(oa, i + 1, ob, p[i])
    nb = ob * p[i]
    print na, na // ob

    oa, ob = na, nb
