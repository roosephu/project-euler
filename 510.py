n = int(1e9)

def gcd(a, b):
    if a == 0:
        return b
    return gcd(b % a, a)

ans = 0
for aa in range(1, 200):
    for bb in range(aa, 200):
        K = n / bb / bb / (aa + bb) / (aa + bb)
        if K == 0:
            break
        if gcd(aa, bb) != 1:
            continue
        a = aa * aa * (aa + bb) * (aa + bb)
        b = bb * bb * (aa + bb) * (aa + bb)
        c = aa * aa * bb * bb
        ans += (K + 1) * K / 2 * (a + b + c)
        print a, b, c, K
print ans
