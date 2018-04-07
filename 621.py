
import numpy as np

p2, p1 = 13 * 3527, 466073
N = 2**19
x = np.zeros(N)
y = np.zeros(N)
z = np.zeros(N)

for i in range(N):
    x[i] = kronecker(i % p1, p1)
for i in range(p2):
    y[-i] = kronecker(i % p2, p2)
    z[-i] = kronecker(i % p2, p2) * (i % p2)

xx = np.fft.fft(x)
yy = np.fft.ifft(xx * np.fft.fft(y))
zz = np.fft.ifft(xx * np.fft.fft(z))

ans = 0
Fp = Integers(p1)
for i in range(p1):
    start = int(Fp(i) / p2) * p2
    ans += int(round(yy[i].real)) * start + int(round(zz[i].real))
print ans

D, f = -13 * 3527 * 466073, 81
ans = 12 * ans / D * (1 - kronecker(D, 2))

w = 0
for d in divisors(f):
    w += moebius(d) * kronecker(D, d) * sigma(f / d, 1)
print ans / 8 * w
