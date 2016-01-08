N = 10**9+ 1
F = {}

def f(dep, diff, offset, lmt):
  if dep < 0:
    if offset == -1 and diff < 0:
      return 1
    return 0
  S = (dep, diff, offset, lmt)
  if S not in F:
    if lmt:
      bnd = N // 5**dep % 5
    else:
      bnd = 5

    ans = 0
    for i in range(bnd + 1):
      if i == bnd and not lmt:
        continue
      for old_offset in [-1, 0, 1]:
        delta = i * 2 + old_offset
        if offset == 1 and delta < 5:
          continue
        if offset == 0 and (delta >= 5 or delta < 0):
          continue
        if offset == -1 and delta >= 0:
          continue
        new_diff = diff
        if delta < 0:
          new_diff -= 1
        elif delta >= 5:
          new_diff += 1
        ans += f(dep - 1, new_diff, old_offset, i == bnd)
    F[S] = ans
  return F[S]

print f(32, 0, 0, True)
print len(F)
