
from time import time
        
def possible(L):
    '''Check if a sequence of bits is a valid sequence'''
    if len(L) <= 1: return True
    for i in range(1, len(L), 2):
        if L[i] == L[i-1]:
            break
    else:
        L = [L[i] for i in range(0, len(L), 2)]
        if possible(L):
            return True
    for i in range(2, len(L), 2):
        if L[i] == L[i-1]:
            break
    else:
        L = [1-L[0]] + [L[i] for i in range(1, len(L), 2)]
        if possible(L):
            return True
    return False

cTab = {}
def cntL(L, k, debug = False):
    '''Returns the number of elements in A, starting with fixed bits given
       by L and having k arbitrary additional bits'''
    T = tuple(L+[k])
    # Check, if we know the result already.
    if T in cTab:
        return cTab[T]
    assert k >= 0
    if not possible(L): return 0
    if k == 0:
        return 1
    ok0 = True
    ok1 = True
    for i in range(1, len(L), 2):
        if L[i] == L[i-1]:
            ok0 = False
            break
    for i in range(2, len(L), 2):
        if L[i] == L[i-1]:
            ok1 = False
    if ok0 and ok1:
        return cntL(L + [0], k-1, debug) + cntL(L + [1], k-1, debug)
    res = 0
    k0 = k
    if ok0:
        if len(L)%2 == 0: k+= 1
        res += cntL(L[::2],k//2, debug)
    if ok1:
        if len(L)%2 == 1: k+=1
        res += cntL([1-L[0]]+L[1::2], k//2, debug)
    cTab[T] = res
    return res

def evb(L, base, mod):
    '''Evaluate a list of bits in base b and reduce the
       result modulo mod'''
    r = 0
    for x in L:
        r = (r*base+x) % mod
    return r

def sumB(base, n, mod):
    '''Return sum(base**i for i in range(n)) % mod'''
    w = pow(base, n, mod*(base-1))
    return w // (base-1)

def nth2(L, k, n, base, mod):
    '''Find nth term in A, which starts with the bits in L
       and has k additional bits and call this sequence S.
       Then compute 3 values:
       (1) Evaluate S in the given base and reduce modulo mod
       (2) Drop the least significant bit of S and evaluate the
        remainder in the given base and reduce modulo mod.
       (3) Get the most significant bit of S.'''       
    if k == 0:
        r = evb(L, base, mod)
        r2 = evb(L[:-1], base, mod)
        return r, r2, L[0]
    # Find out whether the sequence L can be found starting at an even or odd
    # position.
    ok0 = True
    ok1 = True
    for i in range(1, len(L), 2):
        if L[i] == L[i-1]:
            ok0 = False
            break
    for i in range(2, len(L), 2):
        if L[i] == L[i-1]:
            ok1 = False

    assert ok0 or ok1
    # If the sequence can start at both even or odd positions, then we
    # guess the next bit and recurse.
    if ok0 and ok1:
        low = cntL(L + [0], k-1)
        if n <= low:
            return nth2(L + [0], k-1, n, base, mod)
        else:
            return nth2(L + [1], k-1, n-low, base, mod)
    elif ok0:
        expected_length = len(L) + k
        k0 = k
        if len(L)%2 == 0: k+= 1
        returned_length = (len(L)+1) // 2 + k//2
        pop = expected_length < 2*returned_length
        basesq = base*base % mod
        r, r2, msb = nth2(L[::2],k//2, n, basesq, mod)
        sb = sumB(basesq, returned_length, mod)
        sb2 = sumB(basesq, returned_length-1, mod)
        invresn = sb - r
        invresn2 = sb2 - r2
        if not pop:
          val = (invresn + r*base) % mod
          val2 = (r + invresn2*base) % mod
        else:
          val = (r + invresn2*base) % mod
          val2 = (invresn2 + r2*base) % mod
        return val, val2, msb
    elif ok1:
        expected_length = len(L) + k
        k0 = k
        if len(L)%2 == 1: k+=1
        returned_length = 1 + len(L)//2 + k//2
        basesq = base*base % mod
        r, r2, msb = nth2([1-L[0]]+L[1::2], k//2, n, basesq, mod)
        v2 = pow(basesq, returned_length-2, mod)
        v = v2 *basesq % mod
        sb = sumB(basesq, returned_length, mod)
        sb2 = sumB(basesq, returned_length-1, mod)
        invresn = sb - r 
        invresn2 = sb2 - r2
        r -= v*msb
        r2 -= v2*msb
        pop = expected_length < 2*returned_length-1
        if not pop:
          val = (invresn + r*base) % mod
          val2 = (r + invresn2*base) % mod
        else:
          val = (r + invresn2*base) % mod
          val2 = (invresn2 + r2*base) % mod        
        return val, val2, 1-msb

def cntsumK(k):
    '''The number of valid integers < 2**k'''
    if k < 4 : return [0,1,3,6][k]
    m = 3
    cm = 3
    d = 1
    res = 6
    while True:
        if m + d >= k:
            r = k - m
            return res + cm * r + 2*r*(r+1)//2
        res += d *cm + 2*d*(d+1)//2
        m += d
        cm += 2*d
        if m + d >= k:
            r = k - m
            return res + cm * r + r*(r+1)//2
        res += d * cm + d*(d+1)//2
        m += d
        cm += d
        d *= 2


def Asize(m):
    '''Returns the bit length of A(m)'''
    hi = 1
    lo = 0
    while cntsumK(hi) < m:
        lo = hi
        hi *= 2
    while hi - lo > 1:
        mi = (hi + lo) // 2
        if cntsumK(mi) < m:
            lo = mi
        else:
            hi = mi
    assert cntsumK(lo) < m
    assert cntsumK(hi) >= m
    return hi

def A(m, mod):
    b = Asize(m)
    low = cntsumK(b-1)
    res = nth2([1],b-1, m - low, 2, mod)
    return res[0]

def P361(n = 18, mod = 10**9):
    start = time()
    res = sum(A(10**i, mod) for i in range(1,n+1)) % mod
    print('time', time() - start)
    return res

print(P361())

# cnt = [0] * 100
# v = []
# f = set()
# with open("361.txt", "r") as fi :
#     a = fi.readlines()
#     for w in a :
#         a, b = map(int, w.split(' '))
#         x = bin(int(b))[2:]
#         if len(x) <= 56 :
#             print x
#             v += [x]
#             f.add(x)
#             cnt[len(x)] += 1

# v = reversed(sorted(v))
# v = sorted(v)
# lx = '1'
# da = [[0, 0] for i in range(100)]
# for x in v :
#     if len(x) > len(lx) or x != lx[:len(x)] :
#         print x
#     lx = x
    # if (x + '0') in f and (x + '1') in f :
    #     print x

#     if len(x) > 2 :
#         if x[:2] == '10' :
#             da[len(x)][0] += 1
#         else :
#             da[len(x)][1] += 1
# for [a, b] in da :
#     print a, b
# # print cnt
