import sage.all as _

_.forget()

n = 3
dx, dy = _.var('dx, dy')
ans = 0

dist = _.sqrt(dx * dx + dy * dy)
int_xy, int_x, int_y, int_1 = {}, {}, {}, {}

print _.integral(_.integral(dx * dy * dist, (dy, 0, 3)), (dx, 0, 2)).n(100)

f_xy = _.integral(_.integral(dx * dy * dist, dy), dx)
f_y = _.integral(_.integral(dy * dist, dy), dx)
f_x = _.integral(_.integral(dx * dist, dy), dx)
f_1 = _.integral(_.integral(dist, dy), dx)
print f_xy
print f_y.full_simplify()
print f_x.full_simplify()
print f_1.full_simplify()
n = 0

for x in range(n + 1):
  for y in range(n + 1):
    print 'init', x, y
    int_xy[(x, y)] = _.integral(_.integral(dx * dy * dist, (dy, 0, y)), (dx, 0, x))
    int_x[(x, y)] = _.integral(_.integral(dx * dist, (dy, 0, y)), (dx, 0, x))
    int_y[(x, y)] = _.integral(_.integral(dy * dist, (dy, 0, y)), (dx, 0, x))
    int_1[(x, y)] = _.integral(_.integral(dist, (dy, 0, y)), (dx, 0, x))
# print int_xy, int_x, int_y, int_1

def my_eval(f, x1, x2, y1, y2):
  return f[(x2, y2)] - f[(x1, y2)] - f[(x2, y1)] + f[(x1, y1)]

for lx in range(1, n):
  for rx in range(lx + 1, n):
    for ly in range(1, n):
      for ry in range(ly + 1, n):
        print lx, rx, ly, ry
        area = n * n - (rx - lx) * (ry - ly)
        Lx = _.min_symbolic(lx + dx, n)
        Rx = _.min_symbolic(rx + dx, n)
        Ly = _.min_symbolic(ly + dy, n)
        Ry = _.min_symbolic(ry + dy, n)
        func = (n - dx) * (n - dy) - (Rx - Lx) * (Ry - Ly) - (_.max_symbolic(dx, rx) - _.max_symbolic(dx, lx)) * (_.max_symbolic(dy, ry) - _.max_symbolic(dy, ly)) + _.max_symbolic(0, rx - lx - dx) * _.max_symbolic(0, ry - ly - dy)
        print func
        # func = func * _.sqrt(dx * dx + dy * dy)
        x_breaks = sorted([0, lx, rx, n - lx, n - rx, rx - lx, n])
        y_breaks = sorted([0, ly, ry, n - ly, n - ry, ry - ly, n])

        cur = 0
        for x1, x2 in zip(x_breaks, x_breaks[1:]):
          for y1, y2 in zip(y_breaks, y_breaks[1:]):
            _.assume(x1 <= dx, dx <= x2, y1 <= dy, dy <= y2)
            simp = func.full_simplify().polynomial(_.ZZ)
            # print simp
            try:
              for coef, term in zip(simp.coefficients(), simp.monomials()):
                if term == dx * dy:
                  cur += coef * my_eval(int_xy, x1, x2, y1, y2)
                elif term == dx:
                  cur += coef * my_eval(int_x , x1, x2, y1, y2)
                elif term == dy:
                  cur += coef * my_eval(int_y , x1, x2, y1, y2)
                elif term == 1:
                  cur += coef * my_eval(int_1 , x1, x2, y1, y2)
                else:
                  print 'xxx', term, coef
            except:
              cur += float(simp) * my_eval(int_1, x1, x2, y1, y2)
            # print simp, x1, x2, y1, y2, simp.coefficient(dx * dy),
            # cur += _.integral(_.integral(simp, (dy, y1, y2)), (dx, x1, x2))
            _.forget()

        cur = cur * 4 / area / area
        # print cur.n(100), cur
        cur = cur.n(100)
        ans += cur
        # ans += _.integral(_.integral(func, (dy, 0, n)), (dx, 0, n)) * 4 / area / area
        print 'cur = %s, ans = %s' % (cur.n(100), ans.n(100))
