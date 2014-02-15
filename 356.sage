# f = x^3 - 4 * x^2 + 2
# solns = [s[x].n(digits = 10) for s in solve(f, x, solution_dict = true)]
# for i in [0 .. 10] :
#     print sum([s^i for s in solns]), solns[2]^i

GF = Integers(10^8)
expo = 987654321

def find_sum(p, q) :
    init = vector([GF(3), GF(p), GF(p^2)])
    mat = matrix([[GF(0), GF(0), GF(-q)], 
                  [GF(1), GF(0), GF(0) ],
                  [GF(0), GF(1), GF(p) ]])
    dest = init * mat^(expo - 2)
    print dest
    return dest[2]

ans = GF(0)
for i in [1 .. 30] :
    ans += find_sum(2^i, i) - 1
print ans
