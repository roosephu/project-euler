︠1ed142d1-67b8-45fa-a1a5-55cf1293930a︠

︠8339fc1f-e898-4808-9b7e-66fb6cabb33e︠
def dfs(n, pos, S):
    if (S >> (pos - 1) & 1) == 1:
        return 0
    S |= 1 << (pos - 1)
    ret = 0
    if pos == n:
        if S == ((1 << n) - 1):
            return 1
        return 0
    ret = 0
    for i in range(pos - 3, pos + 4):
        if 1 <= i <= n:
            ret += dfs(n, i, S)
    return ret

for i in range(1, 20):
    print dfs(i, 1, 0)
︡9001798a-ff0a-45d4-8572-a76a57768a90︡︡︡︡{"stdout":"1\n1\n1\n2\n6\n14\n28\n56\n118\n254\n541","done":false}︡{"stdout":"\n1140","done":false}︡{"stdout":"\n2401","done":false}︡{"stdout":"\n5074","done":false}︡{"stdout":"\n10738","done":false}︡{"stdout":"\n22711","done":false}︡{"stdout":"\n48001","done":false}︡{"stdout":"\n101447","done":false}
︠199cdd0a-597d-4689-8aa9-2f933ef0a27c︠









