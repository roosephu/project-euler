ans = 0

def calc(s, N):
    l = 1
    for i in range(1, s + 1):
        l = lcm(l, i)
    return N // l - N // lcm(l, s + 1)

print calc(3, 14)

for i in range(1, 32):
    ans += calc(i, 4^i)
print 'ans = %s' % (ans,)