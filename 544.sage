

with open('544.tmp') as f:
  data = map(lambda t: int(t[:-1]), f.readlines())

  GF = Integers(10**9 + 7)
  R = PolynomialRing(GF, 'x')

  def finite_integral(fn):
    ret = 0
    for exp, coef in enumerate(fn):
      ret += coef * (R(bernoulli_polynomial(x, exp + 1)) - R(bernoulli(exp + 1))) / (exp + 1)
    return R(ret)

  poly = R.lagrange_polynomial(list(enumerate(data)))
  print poly
  g = finite_integral(poly)
  # print poly(0)
  print g(1112131415 + 1) - g(1)
