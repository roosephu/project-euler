# f = {}
# Q = []
# s = 0

# def solve(Lx, Ly):
#     global f, Q, s

#     f = {}
#     Q = []
#     s = 0
#     # Lx, Ly = 5, 4
#     def push(x):
#         global s, Q, f
#         if x not in f:
#             Q += [x]
#             f[x] = s
#     push(((0, 0), (Lx - 1, Ly - 1)))

#     beg = 0
#     while beg < len(Q):
#         (rx, ry), (ex, ey) = Q[beg]
#         beg += 1
#         s = f[((rx, ry), (ex, ey))] + 1
#         if rx == Lx - 1 and ry == Ly - 1:
#             # print 'ans = %2d' % (s - 1)
#             # break
#             return s - 1
#         # if s <= 3:
#         #     print s, rx, ry, ex, ey
#         if ex > 0:
#             if ex - 1 == rx and ey == ry:
#                 push(((ex, ey), (rx    , ry)))
#             else:
#                 push(((rx, ry), (ex - 1, ey)))
#         if ey > 0:
#             if ey - 1 == ry and ex == rx:
#                 push(((ex, ey), (rx, ry    )))
#             else:
#                 push(((rx, ry), (ex, ey - 1)))
#         if ex < Lx - 1:
#             if ex + 1 == rx and ey == ry:
#                 push(((ex, ey), (rx    , ry)))
#             else:
#                 push(((rx, ry), (ex + 1, ey)))
#         if ey < Ly - 1:
#             if ey + 1 == ry and ex == rx:
#                 push(((ex, ey), (rx, ry    )))
#             else:
#                 push(((rx, ry), (ex, ey + 1)))
#     return -1

# for Lx in range(1, 20):
#     for Ly in range(1, 20):
#         print "%3d" % (solve(Lx, Ly)),
#     print ""
# # for rx in range(L):
# #     for ry in range(L):
# #         x = ((rx, ry), (1, 0))
# #         if x in f:
# #             print f[x] + 1,
# #         else:
# #             print 0,
# #     print ""

ans = 1
for p in primes(1000000):
    if p == 2:
        continue
    k = p * p
    k = (k - 1) // 2
    ans += k // 12
#     print p, p * p, k // 12
print ans * 2
