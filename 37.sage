ans = 0

def dfs(x) :
    global ans
    if not is_prime(x) :
        return 
    b = True
    p = 10
    while p <= x :
        if not is_prime(x % p) :
            b = False
            break
        p *= 10
        
    if b and x > 10 :
        print x
        ans += x
    for i in [0 .. 9] :
        dfs(x * 10 + i)

for i in [1 .. 9] :
    dfs(i)
print ans
