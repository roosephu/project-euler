from itertools import *

def get_number(t):
  ret = 0
  for i in t:
    ret = ret * 10 + i
  return ret

m = 10
cnt = 0
ans = ""
for perm in permutations(range(m)):
  if perm[0] <= 1:
    continue
  cnt += 1
  if cnt % 10000 == 0:
    print cnt
  for j in range(2, m):
    t = perm[0]
    p = get_number(perm[1:j])
    q = get_number(perm[j:m])

    x = str(t * p) + str(t * q)
    x = list(x)
    if len(x) == m and len(set(x)) == m:
      # print "".join(x), t, p, q, t * p, t * q
      x = "".join(x)
      if x > ans:
        ans = x
        print ans
