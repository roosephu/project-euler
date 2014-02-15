ans = 1
now = 1
delta = 2
LMT = 1001^2
while now < LMT :
    for i in [1 .. 4] :
        now += delta
        ans += now
    delta += 2
print ans
