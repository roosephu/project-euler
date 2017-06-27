︠8908be31-02dc-4662-b1e2-c212c844b55eis︠

def get_line(a, b):
    ax, ay = a
    bx, by = b
    u, v, w = ay - by, bx - ax, ax * by - ay * bx
    if u == 0:
        return 0, v, w / v
    else:
        return 1, v / u, w / u

pos = {}
def add_line(A, B, C):
    global pos

    line = str(get_line(A, C))
    if line not in pos:
        pos[line] = set()
    pos[line].add(str(A))
    pos[line].add(str(B))
    pos[line].add(str(C))

def add_triangle(A, B, C):
    AB = (A + B) / 2
    BC = (B + C) / 2
    CA = (C + A) / 2
    ABC = (A + B + C) / 3
    add_line(A, AB, B)
    add_line(B, BC, C)
    add_line(C, CA, A)
    add_line(A, ABC, BC)
    add_line(B, ABC, CA)
    add_line(C, ABC, AB)

A, B, C = vector([0, 0]), vector([-1 / 2, -sqrt(3) / 2]), vector([1 / 2, -sqrt(3) / 2])
di = B
dj = C - B
dk = B + C

n = 36
for i in range(n):
    print i
    for j in range(i + 1):
        delta = i * di + j * dj
        add_triangle(A + delta, B + delta, C + delta)
        if i < n - 1:
            add_triangle(A + delta + dk, B + delta, C + delta)

def get_intersect(sa, sb):
    for x in sa:
        if x in sb:
            return x
    return None

ans = 0
lines = pos.values()
print '#lines = %d' % (len(lines))
for i in range(len(lines)):
    for j in range(0, i):
        for k in range(0, j):
            a = get_intersect(lines[i], lines[j])
            b = get_intersect(lines[j], lines[k])
            c = get_intersect(lines[k], lines[i])
            if a != None and b != None and c != None and a != b and a != c and b != c:
                ans += 1
print 'ans = %d' % (ans)

︡bdc2ba08-74f7-423a-88e0-b5f4d6c1566d︡︡{"stdout":"0\n1\n2","done":false}︡{"stdout":"\n3","done":false}︡{"stdout":"\n4","done":false}︡{"stdout":"\n5","done":false}︡{"stdout":"\n6","done":false}︡{"stdout":"\n7","done":false}︡{"stdout":"\n8","done":false}︡{"stdout":"\n9","done":false}︡{"stdout":"\n10","done":false}︡{"stdout":"\n11","done":false}︡{"stdout":"\n12","done":false}︡{"stdout":"\n13","done":false}︡{"stdout":"\n14","done":false}︡{"stdout":"\n15","done":false}︡{"stdout":"\n16","done":false}︡{"stdout":"\n17","done":false}︡{"stdout":"\n18","done":false}︡{"stdout":"\n19","done":false}︡{"stdout":"\n20","done":false}︡{"stdout":"\n21","done":false}︡{"stdout":"\n22","done":false}︡{"stdout":"\n23","done":false}︡{"stdout":"\n24","done":false}︡{"stdout":"\n25","done":false}︡{"stdout":"\n26","done":false}︡{"stdout":"\n27","done":false}︡{"stdout":"\n28","done":false}︡{"stdout":"\n29","done":false}︡{"stdout":"\n30","done":false}︡{"stdout":"\n31","done":false}︡{"stdout":"\n32","done":false}︡{"stdout":"\n33","done":false}︡{"stdout":"\n34","done":false}︡{"stdout":"\n35","done":false}︡{"stdout":"\n","done":false}︡{"stdout":"#lines = 321\n","done":false}︡{"stdout":"ans = 343047\n","done":false}︡{"done":true}
︠c885746c-2f77-4e1b-a506-37d9ea0e98fd︠









