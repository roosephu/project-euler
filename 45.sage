T, P, H = set(), set(), set()
for i in [1 .. 100000] :
    T.add(i * (i + 1) / 2)
    P.add(i * (3 * i - 1) / 2)
    H.add(i * (2 * i - 1))

print T & P & H
