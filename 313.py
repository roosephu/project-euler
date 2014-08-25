f = {}
Q = []
s = 0
L = 20
def push(x) :
    global s, Q, f
    if x not in f :
        Q += [x]
        f[x] = s
push(((0, 0), (1, 0)))

beg = 0
while beg < len(Q) :
    (rx, ry), (ex, ey) = Q[beg]
    beg += 1
    s = f[((rx, ry), (ex, ey))] + 1
    # if s <= 3 :
    #     print(s, rx, ry, ex, ey)
    if ex > 0 :
        if ex - 1 == rx and ey == ry :
            push(((ex, ey), (rx    , ry)))
        else :
            push(((rx, ry), (ex - 1, ey)))
    if ey > 0 :
        if ey - 1 == ry and ex == rx :
            push(((ex, ey), (rx, ry    )))
        else :
            push(((rx, ry), (ex, ey - 1)))
    if ex < L :
        if ex + 1 == rx and ey == ry :
            push(((ex, ey), (rx    , ry)))
        else :
            push(((rx, ry), (ex + 1, ey)))
    if ey < L :
        if ey + 1 == ry and ex == rx :
            push(((ex, ey), (rx, ry    )))
        else :
            push(((rx, ry), (ex, ey + 1)))

for rx in range(L) :
    for ry in range(L) :
        x = ((rx, ry), (1, 0))
        if x in f :
            print(f[x] + 1, end = " ")
        else :
            print(0, end = " ")
    print("")
