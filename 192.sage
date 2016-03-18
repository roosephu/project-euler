bound = 10**12
n = 10**5
ans = 0

for i in range(1, n + 1):
    if i % 1000 == 0:
        print i

    if int(math.sqrt(i))**2 == i:
        continue

    x = sqrt(i).n(200).nearby_rational(max_denominator=10**12)
    ans += x.denominator()

print 'ans = %d' % (ans)
