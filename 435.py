# class Matrix :
#     def __init__(self) :
#         self.x = []
    
#     def __mul__(self, x) :

MOD = 1307674368000

def matmul(a, b) :
    n = len(a)
    m = len(b)
    t = len(b[0])

    c = [[0] * t for i in range(n)]
    for i in range(n) :
        for j in range(m) :
            for k in range(t) :
                c[i][k] += a[i][j] * b[j][k]
                c[i][k] %= MOD
    return c


def build(x) :
    return [[0, x**2, 0],
            [1, x, 0],
            [0, 1, 1],]

def fpm(b, e, x) :
    e -= 1
    t = [[0, x, x], 
         [0, 0, 0],
         [0, 0, 0]]
    while e != 0 :
        if e % 2 == 1 :
            t = matmul(t, b)
        b = matmul(b, b)
        e >>= 1
    return t[0][1]

ans = 0
for i in range(101) :
    ans += fpm(build(i), 10**15, i)

print(ans % MOD)
print(fpm(build(11), 7, 11))
