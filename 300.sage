n = 8

ans = 0
for i in range(1, 16):
  p, q = n // i, n % i

  x = p * (i - 1) + (t - 1) * p + (q - 1) + q
  if x > ans:
    ans = x
print ans / 4.
