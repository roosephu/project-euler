import sage.all as _

bn = map(bernoulli, range(10))

def CB(n, m):
  return Combinations(n, m).cardinality()

def S(k, n):
  ret = 0
  for i in range(k + 1):
    ret += n**(k + 1 - i) * bn[i] * CB(k + 1, i) / (k + 1)
  return ret

def ex3gcd(n, k, b, uv):
  k = k.full_simplify()
  if not isinstance(b, _.Integer):
    b = b.full_simplify()
  print n, k, b
  ret = {(u, v): 0 for u in range(uv + 1) for v in range(uv - u + 1)}
  if k == 0:
    for u in range(uv + 1):
      for v in range(uv - u + 1):
        ret[(u, v)] += S(u, n + 1) * floor(b)**v
  elif n <= 3:
    for u in range(uv + 1):
      for v in range(uv - u + 1):
        for i in range(n + 1):
          ret[(u, v)] += i**u * floor(k * i + b)**v
  elif k >= 1:
    floor_k = floor(k)
    saw_k = k - floor_k
    rec = ex3gcd(n, saw_k, b, uv)
    for u in range(uv + 1):
      for v in range(uv - u + 1):
        for j in range(v + 1):
          ret[(u, v)] += CB(v, j) * rec[(u + j, v - j)] * floor_k**j
  elif b >= 1:
    floor_b = floor(b)
    saw_b = b - floor_b
    rec = ex3gcd(n, k, saw_b, uv)
    for u in range(uv + 1):
      for v in range(uv - u + 1):
        for j in range(v + 1):
          ret[(u, v)] += CB(v, j) * rec[(u, v - j)] * floor_b**j
  else:
    y_max = floor(k * n + b)
    rec = ex3gcd(y_max - 1, 1 / k, (1 - b) / k + 1, uv)
    # print 'y_max', y_max
    for u in range(uv + 1):
      for v in range(uv - u + 1):
        ret[(u, v)] += y_max**v * S(u, n + 1)
        # print u, v, ret[(u, v)]
        for j in range(v):
          for i in range(u + 1):
            ret[(u, v)] -= CB(v, j) * rec[(j, u + 1 - i)] * bn[i] * CB(u + 1, i) / (u + 1) # coefficient of y^i
  # print n, k, b, uv, ret, BF(n, k, b, uv)
  return ret

def BF(n, k, b, uv):
  ret = {(u, v): 0 for u in range(uv + 1) for v in range(uv - u + 1)}
  for u in range(uv + 1):
    for v in range(uv - u + 1):
      for i in range(n + 1):
        ret[(u, v)] += i**u * floor(k * i + b)**v
  return ret

def main():
  n = 10**16

  ans = 0
  c = (3 - sqrt(5)) / 2
  # k = sqrt(5) - 2
  # print floor(5 * k)
  # print "bf", BF(n, k, 0, 3)
  # print 'ex', ex3gcd(n, k, 0, 3)

  # for i in range(n + 1):
  #   k = floor(c * i)
  #   # ans += 2 * i * k - k * (k + 1) / 2
  #   ans += -k * k / 2 + 2 * i * k - 1 / 2 * k
  #   print i, ans
  rec = ex3gcd(n, c, 0, 2)
  ans = -rec[(0, 2)] / 2 + rec[(1, 1)] * 2 - rec[(0, 1)] / 2
  print ans

main()
