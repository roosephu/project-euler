import sage.all as _

GF = _.Integers(1000000123)
dim = 127
m = [[0] * dim for i in range(dim)]
odd_states = {}

index = 0
for a in range(6):
  for b in range(6 - a):
    odd_states[(a, b)] = index
    index += 1

def get_state(even_state, odd_state):
  even_idx = even_state
  odd_idx = odd_states[odd_state]
  return odd_idx * 6 + even_idx

for even_state in range(6):
  for odd_state in odd_states.keys():
      state = get_state(even_state, odd_state)
      a, b = odd_state

      if even_state > 0:
        m[state][get_state(even_state - 1, (a, b))] += even_state
      if even_state < 5:
        m[state][get_state(even_state + 1, (a, b))] += 5 - even_state
      if a > 0:
        m[state][get_state(even_state, (a - 1, b + 1))] += a
      if b > 0:
        m[state][get_state(even_state, (a + 1, b - 1))] += b
      if a + b < 5:
        m[state][get_state(even_state, (a + 1, b))] += 5 - a - b

m[dim - 1][dim - 1] = 1
m[dim - 1][get_state(1, (0, 0))] += 4
m[dim - 1][get_state(0, (1, 0))] += 5
trans = _.matrix(GF, m)

def solve(n):
  init = _.matrix(GF, [0] * (dim - 1) + [1])
  accumulator = _.matrix(GF, [[0] * dim] * dim)
  cur = trans
  for i in range(n):
    cur = cur * cur
    accumulator += cur
    print i

  final = init * accumulator
  # for i in range(n):
  #   init = init * trans
  #   print init[0]
  # final = init

  # final = init * trans**n

  ans = 0
  for even_state in range(6):
    for a, b in odd_states.keys():
      if even_state == 0 and b == 0:
        ans += final[0][get_state(even_state, (a, b))]
  return ans

print solve(39)
