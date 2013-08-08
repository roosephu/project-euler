a, b, c = 3, 2, 9

f = [1] * a + [2] * b + [1] * c
print(f)
offset = 0
while True :
    g = []
    b = True
    for i in range(-1, len(f) + 1) :
        x = 0
        if 0 <= i < len(f) :
            x += f[i]
            if x >= 2 :
                x -= 2
        if i > 0 :
            x += f[i - 1] >= 2
        if i + 1 < len(f) :
            x += f[i + 1] >= 2
        g += [x]
        if x >= 2 :
            b = False
    f = g[0:]
    offset += 1
    # print(f)
    if b :
        break

print(sum(f[:offset]))
print(f)
lx, cnt = 0, 0
for i in f :
    if i == 0 :
        if cnt != 0 :
            print(cnt)
        cnt, lx = 0, 0
    else :
        cnt += 1
        lx = 0
