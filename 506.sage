repeats = [1, 2, 3, 4, 3, 2]

GF = Integers(123454321)
pos = 0
num = []
add = []
now = 1

for i in range(15):
  cur, ans = 0, 0
  while cur < i:
    cur += repeats[pos % 6]
    ans = ans * 10 + repeats[pos % 6]
    pos += 1

  num += [ans]
  t = 0
  for x in range(6):
    t = t * 10 + repeats[pos % 6]
    pos = pos + 1
  add += [t]

def get_sum(init, add, n):
  mat = matrix(GF, [[10**6, 0, add], [1, 1, 0], [0, 0, 1]])
  vec = matrix(GF, [init, 0, 1]).T
  final = mat**n * vec
  # print 'final', final.T
  return final[1][0]

print num, add
n = 10**14
ans = GF(0)
for i in range(15):
  if n >= i:
    ans += get_sum(num[i], add[i], (n - i) // 15 + 1)
print ans
