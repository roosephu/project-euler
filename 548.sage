import sage.all as _

n = 10**16
ans = 1 # f[1] = 1
with open('548.mid') as f:
  for line in f:
    if len(line) < 10:
      continue
    struct, val = line[:-1].split(', ')[1].split(' : ')
    exps = map(int, struct.split(' '))
    exps = filter(lambda t: t != 0, exps)
    val = int(val)
    if val > n:
      continue
    new_exps = list(reversed(sorted([y for x, y in _.factor(val)])))
    if new_exps == exps:
      print exps, val, new_exps
      ans += val

print 'answer = %d' % (ans)
