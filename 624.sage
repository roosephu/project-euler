R = Integers(10^9 + 9)
# R = RR
sqrt5 = sqrt(R(5))
a = (1 - 1 / sqrt5) / 2
b = (1 + 1 / sqrt5) / 2

phi1, phi2 = (1 + sqrt5) / 2, (1 - sqrt5) / 2

# for i in range(1, 10):
i = 10**18
print i, a * (1 / (1 - (phi1 / 2)^i) - 1) + b * (1 / (1 - (phi2 / 2)^i) - 1)
