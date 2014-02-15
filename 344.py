# a, b, c = 3, 2, 9

# f = [1] * a + [2] * b + [1] * c
# print(f)
# offset = 0
# while True :
#     g = []
#     b = True
#     for i in range(-1, len(f) + 1) :
#         x = 0
#         if 0 <= i < len(f) :
#             x += f[i]
#             if x >= 2 :
#                 x -= 2
#         if i > 0 :
#             x += f[i - 1] >= 2
#         if i + 1 < len(f) :
#             x += f[i + 1] >= 2
#         g += [x]
#         if x >= 2 :
#             b = False
#     f = g[0:]
#     offset += 1
#     # print(f)
#     if b :
#         break

# print(sum(f[:offset]))
# print(f)
# lx, cnt = 0, 0
# for i in f :
#     if i == 0 :
#         if cnt != 0 :
#             print(cnt)
#         cnt, lx = 0, 0
#     else :
#         cnt += 1
#         lx = 0

from random import *

f = {}

def get(state, pos) :
    if pos == 0 :
        return 0
    global f

    cur = (tuple(state), pos)
    if cur in f :
        return f[cur]
    d = set()
    d.add(get(state[1:], pos - 1))
    
    lx = 0
    for i, v in enumerate(state) :
        for r in range(lx, v - 1) :
            state[i] = r + 1
            d.add(get(state, pos))
        state[i] = v
        lx = v    

    x = 0
    while x in d :
        x += 1
    f[cur] = x
    return x

def process(state) :
    state = list(state)
    for i in range(len(state) - 1, 0, -1) :
        state[i] -= state[i - 1] + 1
    return state
    
def find(state) :
    state = process(state)
    i = 1
    ret = []
    while i <= len(state) :
        ret += [state[-i]]
        i += 2
    return ret
    
D = {}
for i in range(1) :
    n = randint(2, 10)
    n = 6
    state = sorted(sample(range(1, 20), n))
    pos = randint(1, n)
    # pos = n - 2
    cur = (tuple(state), pos)
    # cur = ((3, 6, 8, 11, 16), 3)
    # cur = ((1, 2, 3, 4), 4)
    print(cur)
    if cur not in D :
        state, pos = cur
        state = list(state)
        D[cur] = get(state, pos)

def pos1(state) :
    i = 1
    sg = 0
    while i <= len(state) :
        sg ^= state[-i] - 1
        i += 2
    return sg + 1
    
def strip(state, y) :
    ret = []
    for i in y :
        ret += [state[i]]
    return ret
    
g = {}
T = {}
for [state, pos], res in sorted(f.items()) :
    # print(state, pos, res)
    if pos == 2 :
        # y = tuple(strip(process(state), [-1, -3]))
        y = tuple(find(state))
        # print(pos, y, res)
        # cur = (y, len(state))
        cur = (y, pos)
        if cur in g :
            T[cur] += [state]
            if (g[cur] ) != (res) :
                print(cur, T[cur], g[cur], res)
                assert(0)
        else :
            g[cur] = res
            T[cur] = [state]

for state, res in sorted(g.items()) :
    if True or res == 0 :            
        print(state, res)
