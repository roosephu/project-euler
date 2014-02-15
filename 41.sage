ans = 0
for T in [1 .. 9] :
    for x in permutations([1 .. T]) :
        s = sum([i * 10 ** j for j, i in enumerate(x)])
        if is_prime(s) :
            ans = max(ans, s)
            print s, i, ans
