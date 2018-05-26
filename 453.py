from numba import jit
from math import gcd
import numpy as np

h, w = 3, 2
# g = gcd(h, w)

# @jit
# def func(h, w):
#     ans = 0
#     S = []
#     for i in range(h + 1):
#         for j in range(w + 1):
#             area = i * w + h * j
#             ans += abs(h * w - area)
#     # print(sorted(S))
#     return ans * 2

# g = 5
# ans1 = func(h * g, w * g)

# print(ans1)

MOD = 135707531
inv2 = np.int64(pow(2, MOD - 2, MOD))
inv3 = np.int64(pow(3, MOD - 2, MOD))
inv6 = np.int64(pow(6, MOD - 2, MOD))
inv24 = np.int64(pow(24, MOD - 2, MOD))

@jit(nopython=True)
def C2(n):
    n = n % MOD
    return n * (n - 1) % MOD * inv2 % MOD

@jit(nopython=True)
def C3(n):
    n = n % MOD
    return n * (n - 1) % MOD * (n - 2) % MOD * inv6 % MOD

@jit(nopython=True)
def C4(n):
    n = n % MOD
    return n * (n - 1) % MOD * (n - 2) % MOD * (n - 3) % MOD * inv24 % MOD

@jit(nopython=True)
def gcd(a, b):
    return b if a == 0 else gcd(b % a, a)

@jit(nopython=True)
def case_3_4(h, w):
    g = gcd(h, w)
    h, w = h // g, w // g
    T = h * w % MOD * (h * w - 1) // 2 % MOD
    if h < w:
        for i in range(h + 1):
            ub = (h * w + h - 1 - w * i) // h
            T -= w * i % MOD * ub % MOD + h * ub % MOD * (ub - 1) % MOD * inv2 % MOD
    else:
        for j in range(w + 1):
            ub = (h * w + w - 1 - h * j) // w
            T -= h * j % MOD * ub % MOD + w * ub % MOD * (ub - 1) % MOD * inv2 % MOD
        # for j in range(w + 1):
        #     if i * w + j * h < h * w:
        #         T -= i * w + j * h
    T = (T % MOD + MOD) % MOD

    hw = h * w % MOD
    ans2 = 0
    ans2 += C2(g + 1) * C2(hw)
    ans2 += hw * hw % MOD * 2 * C3(g + 1) % MOD
    ans2 += 2 * C2(g + 1) * h % MOD * w % MOD
    ans2 -= g * T % MOD + C2(g) * C2(h) % MOD * C2(w) % MOD * 2
    ans2 = ans2 % MOD * g % MOD
    ans2 = ((h * g + 1) * (w * g + 1) % MOD + (g + 1)) % MOD * inv2 % MOD * hw % MOD * g % MOD * g % MOD - ans2
    ans2 = (ans2 % MOD + MOD) % MOD
    # ans2 *= g
    # print(ans2)
    return ans2 * 4 % MOD

# print(case_3_4(h * g, w * g))
case_3_4.inspect_types()

@jit(nopython=True)
def case_1(h, w):
    ans = C2(h) * C2(w) % MOD * 3
    return ans * 4 % MOD

@jit(nopython=True)
def case_2(h, w):
    ans = h * w % MOD * (h + w - 2) % MOD
    return ans * 2 % MOD

@jit(nopython=True)
def calc(H, W):
    ans = 0
    for h in range(1, H + 1):
        print(h)
        for w in range(1, W + 1):
            ans += (case_1(h, w) + case_2(h, w) + case_3_4(h, w)) % MOD * (H - h + 1) % MOD * (W - w + 1) % MOD
    ans = (ans % MOD + MOD) % MOD
    return ans

# def cross(p1, p2, p3):
#     x1, y1 = p1
#     x2, y2 = p2
#     x3, y3 = p3
#     return x1 * y2 - x2 * y1 + x2 * y3 - x3 * y2 + x3 * y1 - x1 * y3

# def calc_bf(H, W):
#     points = [(i, j) for i in range(H + 1) for j in range(W + 1)]
#     n = len(points)
#     ans = 0
#     for a in range(n):
#         for b in range(a):
#             for c in range(b):
#                 ans += abs(cross(points[a], points[b], points[c]))
#     return ans

# print(calc_bf(5, 3))
# print(calc(5, 3))
# print(case_3_4(5, 4), func(5, 4))

# @jit
# def diff(H, W, h, w):
#     t = min(H // h if h else 10**9, W // w if w else 10**9)
#     xs = np.arange(t + 1)
#     ys = (H + 1 - xs * h) * (W + 1 - xs * w)
#     ys = ys - 2 * np.r_[ys[1:], 0] + np.r_[ys[2:], 0, 0]
#     ans = np.sum((xs + 1) * (xs + 1) * xs * (xs + 2) // 6 * ys)
#     # print(h, w, ys, ans)
#     return ans

@jit(nopython=True)
def borders(H, W):
    ans = 0
    for h in range(H + 1):
        for w in range(W + 1):
            if h != 0 or w != 0:
                ans += (H + 1 - h) * (W + 1 - w) % MOD * (H + 1) % MOD * (W + 1) % MOD * gcd(h, w) % MOD * (1 + (h != 0 and w != 0))
            # if gcd(h, w) == 1:
            #     ans -= diff(H, W, h, w) * (1 + (h != 0 and w != 0))
    ans = (ans % MOD + MOD) % MOD
    return ans

# def borders_bf(H, W):
#     points = [(i, j) for i in range(H + 1) for j in range(W + 1)]
#     n = len(points)
#     ans = 0
#     for a in range(n):
#         for b in range(a):
#             for c in range(b):
#                 x1, y1 = points[a]
#                 x2, y2 = points[b]
#                 x3, y3 = points[c]
#                 if cross(points[a], points[b], points[c]) != 0:
#                     ans += abs(gcd(x1 - x2, y1 - y2)) + abs(gcd(x2 - x3, y2 - y3)) + abs(gcd(x3 - x1, y3 - y1))
#     return ans

# print(borders_bf(1, 2))
# print(borders(1, 2))

@jit(nopython=True)
def collinear(H, W):
    n = (H + 1) * (W + 1)
    ans = C4(n)
    num_triangles = C3(n)
    borders = 0
    for h in range(H + 1):
        if h % 100 == 0:
            print(h)
        for w in range(W + 1):
            if gcd(h, w) == 1:
                coef = 1 + (h != 0 and w != 0)
                t = min(H // h if h else n, W // w if w else n)
                xs = np.arange(t + 1)
                # print(xs.dtype)
                ys = (H + 1 - xs * h) * (W + 1 - xs * w)
                tmp = ys.copy()
                ys[:-1] -= 2 * tmp[1:]
                ys[:-2] += tmp[2:]
                # ys = ys - 2 * np.r_[ys[1:], 0] + np.r_[ys[2:], 0, 0]
                ys = ys % MOD
                # print(h, w, ys)
                ans -= np.sum((xs + 1) * xs % MOD * (xs - 1) % MOD * (xs - 2) % MOD * inv24 % MOD * ys % MOD) * coef
                ans -= np.sum((xs + 1) * xs % MOD * (xs - 1) % MOD * inv6 % MOD * ys % MOD * (n - xs - 1) % MOD) * coef
                num_triangles -= np.sum((xs + 1) * xs % MOD * (xs - 1) % MOD * inv6 % MOD * ys % MOD) * coef
                borders += np.sum((xs + 1) * (xs + 1) % MOD * xs % MOD * (xs + 2) % MOD * inv6 % MOD * ys) * coef
    ans = (ans % MOD + MOD) % MOD
    num_triangles = (num_triangles % MOD + MOD) % MOD
    borders = (borders % MOD + MOD) % MOD
    return ans, num_triangles, borders

# def collinear_bf(H, W):
#     points = [(i, j) for i in range(H + 1) for j in range(W + 1)]
#     n = len(points)
#     ans = 0
#     num_triangles = 0
#     for a in range(n):
#         for b in range(a):
#             for c in range(b):
#                 num_triangles += cross(points[a], points[b], points[c]) != 0
#                 for d in range(c):
#                     if cross(points[a], points[b], points[c]) != 0 and \
#                         cross(points[b], points[c], points[d]) != 0 and \
#                         cross(points[c], points[d], points[a]) != 0 and \
#                         cross(points[d], points[a], points[b]) != 0:
#                         ans += 1
#     return ans, num_triangles

# print(collinear(2, 2))
# print(collinear_bf(2, 2))

# @jit(nopython=True)
def solve(H, W, C):
    total, num_triangles, num_borders = collinear(H, W)
    # C = calc(H, W)
    concave = (C * inv2 % MOD + num_triangles - (borders(H, W) - num_borders) * inv2 % MOD) % MOD
    convex = total - concave
    # print(concave, convex, num_triangles)
    ans = concave * 3 + convex
    ans = (ans % MOD + MOD) % MOD
    return ans

# print(solve(123, 45))
print(solve(12345, 6789, 42357419))
# print(calc(12345, 6789))
# print(calc(2, 2))
# print(borders(2, 2))

