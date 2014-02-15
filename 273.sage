p = []
for a in primes(150) :
    if a % 4 == 1 :
        for x in [1 .. 100] :
            y = floor(sqrt(a - x * x))
            if x * x + y * y == a :
                p += [[x, y]]
                break

ans = 0
def dfs(a, b, dep) :
    global ans
    if a > b :
        a, b = b, a
    if dep < 0 :
        ans += a
        return 
    c, d = p[dep]
    dfs(a, b, dep - 1)
    dfs(abs(a * c - b * d), a * d + b * c, dep - 1)
    dfs(abs(a * d - b * c), a * c + b * d, dep - 1)

dfs(0, 1, 16 - 1)
print ans / 2

# http://web.maths.unsw.edu.au/~mikeh/webpapers/paper21.pdf
