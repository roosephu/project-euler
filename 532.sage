theta, a = var('theta, a')
init = acos(0.999)
assume(a > 0)
nums = 827
const = (sin(2 * pi / nums) / (1 - cos(2 * pi / nums))).n(100)
init = acos(0.999)
final = pi / 2
print numerical_integral(sqrt(sin(theta)^2 + const^2) / sin(theta), init, final)[0] * 827
