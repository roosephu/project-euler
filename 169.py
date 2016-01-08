S = {}

def f(x):
    if x == 0:
        return 1
    if x in S:
        return S[x]
    if x % 2 == 1:
        return f((x - 1) / 2)
    S[x] = f(x / 2) + f(x / 2 - 1)
    return S[x]

print f(10**25)
