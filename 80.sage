ans = 0
for i in [1 .. 100] :
    a = n(sqrt(i), digits = 108)
    if floor(a) == a :
        continue
    a = str(a)
    if len(a) < 100 :
        continue
    a = ''.join(a.split('.'))
    for j in [0 .. 99] :
        ans += int(a[j])
print ans
