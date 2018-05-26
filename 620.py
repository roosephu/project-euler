from numba import jit

@jit
def solve(s, p, q):
    L, R = 1e-3, 0.999 * np.pi
    limit = 2 * np.pi
    for i in range(100):
        alpha = (L + R) / 2
        ratio = (s + q) / np.sin(alpha)
        beta = np.arcsin((s + p) / ratio)
        t = np.sin(alpha - beta) * ratio
        if t <= p + q - limit:
            L = alpha
        else:
            R = alpha
    obj = (beta * (s + q) + alpha * (s + p)) / np.pi
#     print(s, p, q, alpha, obj)
    return int(obj)

# solve(9, 5, 6)

@jit('i8(i8)')
def PE620(n):
    ans = 0
    for s in range(5, n):
        print(s)
        for p in range(5, n):
            if s + p > n: break
            for q in range(p + 1, n):
                if s + p + q > n: break
                tmp = solve(s, p, q)
#                 print(s, p, q, tmp)
                ans += tmp
    # solve(5, 5, 6)
    return ans

print(PE620(500))
