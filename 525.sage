theta = var('theta')
a, b = 3., 4.
sin_phi = b * cos(theta) / sqrt(a * a * sin(theta)^2 + b * b * cos(theta)^2)
cos_phi = a * sin(theta) / sqrt(a * a * sin(theta)^2 + b * b * cos(theta)^2)
dx = sqrt(a * a * sin(theta)^2 + b * b * cos(theta)^2) + (a * cos(theta) * cos_phi - b * sin(theta) * sin_phi).diff(theta)
dy = (a * cos(theta) * sin_phi + b * sin(theta) * cos_phi).diff(theta)

print 4 * numerical_integral(sqrt(dx * dx + dy * dy), -pi / 2, 0)[0]

# X = a * cos(theta) * cos_phi - b * sin(theta) * sin_phi
# Y = a * cos(theta) * sin_phi + b * sin(theta) * cos_phi
# T = -pi.n(100) / 2 + 0.001
# print X(theta=T), Y(theta=T), (a * cos(theta))(theta=T), (b * sin(theta))(theta=T)

ans = 22.1503299376 + 22.54888813
print ans
