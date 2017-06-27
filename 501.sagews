︠0ed9c813-08bd-4a6c-9db1-9f7782220dc1︠

︠541c8bcb-00f2-4651-9648-0f5923a566ccs︠
LMT = 10**12
ans = 0

L = list(primes(1000000))
for p in L:
    z = p**7
    if z <= LMT:
        ans += 1

for p in L:
    q = LMT // p**3
    if q == 0:
        break
    ans += prime_pi(q)
    if q >= p:
        ans -= 1

print 'last part'
for p in range(len(L)):
    if L[p]**3 > LMT:
        break
    for q in range(p + 1, len(L)):
        r = LMT // L[p] // L[q]
        if r <= L[q]:
            break
        ans += prime_pi(r, 1000) - prime_pi(L[q], 1000)

print ans
︡6dbdef4a-ed3e-4021-8e13-877e30c166d8︡︡{"stdout":"last part\n","done":false}︡{"stdout":"197912312715\n","done":false}︡{"done":true}︡{"stdout":"197912312715\n","done":false}︡{"done":true}
︠f9fba840-4b40-48ac-b63b-c44dcff9570c︠









