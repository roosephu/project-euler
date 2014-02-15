
ans = 0
q = 0
for p in primes(1100000) :
    if p > 5 :
        l = len(str(q))
        x = CRT(q, 0, 10^l, p)
        ans += x
        # print p, q, x
    q = p
    if p > 1000000 :
        break
print ans
