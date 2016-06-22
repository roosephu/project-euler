# https://projecteuclid.org/download/pdf_1/euclid.em/1048515811
N = 10
P = 137
R = Zp(P, prec = 100, type = 'capped-abs', print_mode = 'series')
# coef = [R(bernoulli(i) * P^(2 * i)) for i in range(N)]
# print R(R(1) / 3 + R(2*3 + 3^2 + 3^3 + 3^4 + 3^5 + 3^6 + 3^7 + 3^8 + 3^9 + 
#                      3^10 + 3^11 + 3^12 + 3^13 + 3^14 + 3^15 + 3^16 + 3^17 + 3^18 + 3^19))

x = matrix(R, [[i^(2 * j) for j in range(1, N + 1)] for i in range(1, N + 1)])
H = [0] * (100 + N * P + 1)
for i in range(100 + N * P):
#     print b[i], b[i + 1]
    H[i + 1] = H[i] + R(1) / (i + 1)
x = x^-1
b = [H[n * P] - H[n] / P for n in range(1, N + 1)]
# print b[0]
# print R(1) + R(1) / 2
coef = [R(0) for i in range(N)]
for i in range(N):
    for j in range(N):
        coef[i] += x[i][j] * b[j]
# coef = x^-1 * b
# print coef

ans = 0

def dfs(n, H_n):
#     if n > 100:
#         return
    # compute H_{np}
    global ans
    if ans < n:
        ans = n

    H_np = H_n / P
    for k in range(1, N + 1):
        H_np += coef[k - 1] * n^(2 * k)
    print n, H_n.ordp(), H_np.ordp()

    for i in range(P):
        if i > 0:
            H_np = H_np + R(1) / (n * P + i)
        if n == 6:
            print n * P + i, H_np.ordp()
        if n * P + i > 0 and H_np.ordp() >= 1:
            dfs(n * P + i, H_np)

# print R(1) + R(1) // 2
# print (R(1) + R(1) // 2) // 3 + R(1) + R(1) // 2 + R(1) // 4 + R(1) // 5 + R(1) // 7
dfs(0, R(0))
# print H[24]
print 'ans = %d' % (ans * P + P - 1)
