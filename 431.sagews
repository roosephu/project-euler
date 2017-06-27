︠fa8bb4eb-6502-415d-bd10-474b66deb4dcs︠
# NSolve[NIntegrate[NIntegrate[rho Sqrt[rho^2+t^2 - 2*rho*t*Cos[theta]], {rho, 0, 3}], {theta, 0, 2 Pi}] /Sqrt[3] == 36, t]

# 36: 1.114785284
t = var('t') #2.511167869
print t
ratio = N(tan(pi / 180 * 40), 100)
max_r = 6
eps = 1e-11

ff = lambda t: numerical_integral(lambda rho: numerical_integral(lambda theta: rho * sqrt(rho*rho + t * t - 2 * rho * t * cos(theta)), 0, 2 * pi, eps_rel=eps, eps_abs=eps)[0], 0, max_r, eps_rel=eps, eps_abs=eps)[0]
print ff(0) * ratio, ff(max_r) * ratio

ans = 0
for i in range(20, 26):
    cur_ans = find_root(lambda t: ff(t) * ratio - i * i, 0, max_r)
    print i, cur_ans
    ans += cur_ans
print ans

# print find_root(lambda t: ff(t) * ratio - 36, 0, 3)
︡f6f2c6e5-f89b-4fcf-8660-5d69b5780e89︡{"stdout":"t\n"}︡{"stdout":"379.599730119"}︡{"stdout":" "}︡{"stdout":"644.428516744\n"}︡{"stdout":"20"}︡{"stdout":" 1.60975850093\n21"}︡{"stdout":" 2.80601194654\n22"}︡{"stdout":" 3.67832791544\n23"}︡{"stdout":" 4.42640329178\n24"}︡{"stdout":" 5.10942020745\n25"}︡{"stdout":" 5.75610718951\n"}︡{"stdout":"23.3860290517\n"}︡
︠569b0eb0-ea36-4c77-a2dd-e7da9c09dbef︠









