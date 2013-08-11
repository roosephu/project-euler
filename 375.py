primes = [1000000007, 1000000009, 3214567, 1000000021, 1000000033]
rem = [667990651, 797334924, 2090285, 573401801, 349470814]

prod = 1
for i in primes :
    prod *= i
ans = 0
for i, j in zip(primes, rem) :
    t = prod // i
    inv = pow(t, i - 2, i)
    ans += inv * t * j
print(ans % prod)
for i, j in zip(primes, rem) :
    print(ans % i, j)
