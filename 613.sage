beta2 = acos(0.8)
beta1 = acos(0.6)
f = lambda beta: beta - numerical_integral(tan(x) / tan(beta), 0, beta)[0]
1 / 4 + (f(beta1) + f(beta2)) / 2 / pi
