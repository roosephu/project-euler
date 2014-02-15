ans = 0
for i in [1 .. 50000000] :
    if i % 100000 == 1 :
       print i
    if is_prime(i * i * 2 - 1) :
       ans += 1
print ans
