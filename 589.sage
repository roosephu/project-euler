%%cython --annotate
import numpy as np
cimport numpy as np

def get_mat(long L, long R):
    cdef int x, a, b, Lp
    cdef np.ndarray[np.float64_t, ndim=2] A = np.zeros((R + 6, R + 6), dtype=np.float64)
    cdef np.ndarray[np.float64_t, ndim=1] v = np.zeros(R + 6, dtype=np.float64)
    for x in range(R + 6):
        A[x, x] = (R - L + 1) * (R - L + 1)
        v[x] = 5 * (R - L + 1) * (R - L + 1)

        Lp = max(x - 5, L)
        v[x] += (R - L + 1) * (Lp - L) * (L + Lp - 1) / 2.

#         thres1, thres2 = L + x - Lp, x
#         for d in range(L + x - R, R + x - Lp + 1): # d = b - a
#             if d < thres1:
#                 cnt = d - (L + x - R) + 1
#                 avgA = R - (cnt - 1) / 2.
#                 avgB = avgA + d
#             elif d < thres2:
#                 cnt = R - Lp + 1
#                 avgA = (R + Lp) / 2.
#                 avgB = avgA + d
#             else:
#                 cnt = R + x - Lp + 1 - d
#                 avgB = R + x - (cnt - 1) / 2.
#                 avgA = avgB - d
#             A[x, abs(d)] -= cnt
#             v[x] += (avgB if d <= 0 else avgA) * cnt

        for a in range(Lp, R + 1):
            for b in range(L + x, R + x + 1):
                if a <= b:
                    v[x] += a
                    A[x, b - a] -= 1.
                else:
                    v[x] += b
                    A[x, a - b] -= 1.
#     print A, v
    f = np.linalg.solve(A, v)
    return f[0] - 5
#     return 0

import time
ans = 0
K = 100
t0 = time.time()
for L in range(1, K):
    print L, time.time() - t0
    for R in range(L, K):
        ans += get_mat(L, R + 1)
print "%.6f" % ans
