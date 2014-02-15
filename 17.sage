ans = -4
with open("a000027.txt", "r") as fin :
    for i in [0 .. 1000] :
        x = fin.readline().split(' ')[2][:-1]
        ans += len(x)
        print x
print ans + 3 * (900 - 9)
