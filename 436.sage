# print n(20/17, digits = 20)
t = var('t')

P = e - e^(1 - x) # pdf of player 1
print integral(P * x, x, 0, 1).n(30)

Q = integral((e - 1 - t) * e^t, t, 1 - x, 1)
print integral(Q * x, x, 0, 1).n(30)

ans = integral(Q * integral(P, x, 0, x), x, 0, 1)
print ans, ans.n(digits = 20)
