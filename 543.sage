def S(n):
  ans = 0
  ans += prime_pi(n) # k = 1

  if n >= 4: # k = 2 and odd i
    ans += prime_pi(n - 2) - 1
  ans += n // 2 - 1 # k = 2 and even i

  if n >= 5: # k >= 3
    beg, end = n - 5, (n - 1) % 2
    ans += (beg + end) * ((beg - end) / 2 + 1) / 2
  return ans

ans = 0
for i in range(3, 45):
  print n
  n = fibonacci(i)
  ans += S(n)
# print S(10), S(100), S(1000)

print ans
