
GF = Integers(1234567891011)

def fib(x) :
    a = matrix(GF, [0, 1])
    b = matrix(GF, [[0, 1], 
                    [1, 1]])
    return (a * b^(x - 1))[0][1]

ans = GF(0)
x = 10^14
for i in [1 .. 10^5] :
    x = next_prime(x)
    ans += fib(x)
    print i, x, ans
print ans
