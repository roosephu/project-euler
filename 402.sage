# def calc() :
    

# for i in [0 .. 23] :
#     ans += calc(i, fibonacci(i) % 6)

for n in [1 .. 10] :
    ans = 0
    for a in [1 .. n] :
        for b in [1 .. n] :
            for c in [1 .. n] :
                t = 1
                if (a + b + c) % 2 == 1 :
                    t *= 2
                    if a % 2 == 0 and b % 2 == 1 and (a + b + c + 1) % 4 == 0 :
                        t *= 2
                if b % 3 == 2 and (a + c) % 3 == 0 :
                    t *= 3
                ans += t
    print ans
