︠c6dd103c-a2d1-4752-872c-3c18f6b4e129s︠
t = var('t')
v = var('v')
xx = (1 - t)**3 * 1 + 3 * t * (1 - t)**2 * 1 + 3 * t**2 * (1 - t) * v
yy = 3 * t * (1 - t)**2 * v + 3 * t**2 * (1 - t) + t**3
area = integrate(derivative(xx, t) * yy, (t, 1, 0))
sols = solve(area - pi / 4, v, solution_dict=True)

actual_v = sols[0]
print actual_v[v].n(100)

obj = (sqrt(derivative(xx, t)**2 + derivative(yy, t)**2))(v=actual_v[v])
print obj
arc = numerical_integral(obj, 0, 1)[0]
print arc, (100 * (arc / (pi / 2) - 1)).n(100)

︡24a2b447-fd26-4d52-a053-3c07b68e9381︡︡{"stdout":"0.55177847780446771784543740729\n","done":false}︡{"stdout":"sqrt(((t - 1)^2*(sqrt(-15*pi + 66) - 6) + 2*(t - 1)*t*(sqrt(-15*pi + 66) - 6) + 6*(t - 1)*t)^2 + (2*(t - 1)*t*(sqrt(-15*pi + 66) - 6) + t^2*(sqrt(-15*pi + 66) - 6) + 6*(t - 1)*t)^2)\n","done":false}︡{"stdout":"1.57079691127 0.000037209090614030746652863416716\n","done":false}︡{"done":true}
︠a7c0d244-f1f7-4be6-9e57-da621b0b3cf7︠









