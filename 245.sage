for n in range(2, 10000):
  f = euler_phi(n)
  if (n - 1) % (n - f) == 0 and f != n - 1:
    print n, factor(n), (n - 1) / (n - f)
