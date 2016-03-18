n = 10**14
GF = Integers(10**9 + 7)
R = PolynomialRing(GF, 'x')

def print_values():
  f = [1]
  cur = 1
  for i in range(1, 20):
    cur += f[i // 2]
    f += [cur]
    print i, cur

def main():
  print_values()
  x = var('x')

  def comb(n, m):
    ret = 1
    for i in range(m):
      ret = ret * (n - i) / (i + 1)
    return ret

  def finite_integral(fn):
    ret = 0
    for exp, coef in enumerate(fn):
#       for i in range(exp + 1):
#         ret += coef * bernoulli(i) * comb(exp, i) * x**(exp + 1 - i) / (exp + 1)
      ret += coef * (R(bernoulli_polynomial(x, exp + 1)) - R(bernoulli(exp + 1))) / (exp + 1)
    return R(ret)

  def f(n, k, T={}):
    if (n, k) not in T:
      print 'f(n = %s, k = %s)' % (n, k)
      if n < k:
        ret = n + 1
      else:
        new_n = n // k
        f_new_n = f(new_n, k)
        ret = ff(R(1), new_n, k) * k - f_new_n * ((new_n + 1) * k - n - 1)
      T[(n, k)] = ret
    return T[(n, k)]

  def ff(fn, n, k, T={}): # sum_{i=0}^n fn(i) * f(i)
    coeffs = list(fn)
    if any(coeffs[:-1]):
      ret = 0
      for exp, coef in enumerate(coeffs):
        ret += coef * ff(R(x**exp), n, k)
      return ret

    coef, exp = coeffs[-1], len(coeffs) - 1
    if (n, k, exp) not in T:
      print 'ff(n = %s, k = %s, exp = %s)' % (n, k, exp)
      ret = 0
      if n < k:
        for i in range(n + 1):
          ret += fn(x=i) * (i + 1)
      else:
        new_n = n // k

        g = finite_integral(fn)
        new_fn = (g(x=(new_n + 1) * k) - g(x=(x + 1) * k)) * k
        for i in range(k):
          new_fn += fn(x=x * k + i) * (i + 1)
        new_fn = R(new_fn)
        # print 'fn = %s, n = %s, k = %s, new_n = %s, g = %s, new_fn = %s' % (fn, n, k, new_n, g, new_fn)
        ret = ff(new_fn, new_n, k)
        for i in range(n + 1, (new_n + 1) * k):
          ret -= fn(x=i) * f(i, k)
        # print 'f_new_n', f_new_n
        # print 'fn = %s, n = %s, k = %s, ret = %s' % (fn, n, k, ret)
      T[(n, k, exp)] = ret
    return T[(n, k, exp)] * coef

  # print f(100, 7)
  # return
  ans = 0
  for i in range(2, 11):
    ans += f(n, i)
  print ans
  # print ff(x * 0 + 1, 1, 2)
  # print finite_integral(x)(x=10)

if __name__ == '__main__':
  main()
