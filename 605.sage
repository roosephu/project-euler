n, k = 10^8 + 7, 10^4 + 7
print power_mod(2, n, n)
R = Integers(10^20)
aux = R(2)^n - 1
print R(2)^(n-k) * (aux * (k - 1) + n) * aux^2