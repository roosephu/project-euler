ans = 10^10

def chk(x, y) :
    return sorted(str(x)) == sorted(str(y))

for i in [2 .. (10^7 - 1)] :
    t = euler_phi(i)
    if chk(i, t) :
        if i / t < ans :
            ans = i / t
            print i, t, ans
print ans
