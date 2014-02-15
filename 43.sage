a = primes_first_n(7)
ans = 0
for T in permutations([0 .. 9]) :
    if T[0] == 0 :
        continue
    b = True
    for i in [1 .. 7] :
        s = 100 * T[i] + 10 * T[i + 1] + T[i + 2]
        if s % a[i - 1] != 0 :
            b = False
            break
    # print x

    if b :
        x = sum([i * 10^(9 - j) for j, i in enumerate(T)])
        print x
        ans += x
print ans
