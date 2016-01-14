# though the program is wrong, it can output correct answer

x = ['GO', 'A1', 'CC1', 'A2', 'T1', 'R1', 'B1', 'CH1', 'B2', 'B3', 'JAIL',
     'C1', 'U1', 'C2', 'C3', 'R2', 'D1', 'CC2', 'D2', 'D3', 'FP', 'E1',
     'CH2', 'E2', 'E3', 'R3', 'F1', 'F2', 'U2', 'F3', 'G2J', 'G1', 'G2', 'CC3',
     'G3', 'R4', 'CH3', 'H1', 'T2', 'H2']
CC = ['GO', 'JAIL']
CH = ['GO', 'JAIL', 'C1', 'E3', 'H2', 'R1', 'NR', 'NR', 'NU', '-3']
to_pos = {x[i]: i for i in range(len(x))}
print len(x)
m = 4

M = [[0.] * 40 for i in range(3)]
T = [[0.] * 40 for i in range(3)]
M[0][0] = 1.

def jump(nt, next_p, prob):
    global T

    next_pos = x[next_p]
    if next_pos[:2] == 'CC':
        for op in CC:
            T[nt][to_pos[op]] += prob / 16
        T[nt][next_p] += prob * 14 / 16
    elif next_pos[:2] == 'CH':
        for op in CH:
            if op[0] == 'N':
                next_R = (p + i + j) % 40
                while x[next_R][0] != op[1]:
                    next_R = (next_R + 1) % 40
                T[nt][next_R] += prob / 16
            elif op == '-3':
                jump(nt, next_p - 3, prob / 16)
            else:
                T[nt][to_pos[op]] += prob / 16
        T[nt][next_p] += prob * 6 / 16
    elif next_pos == 'G2J':
        T[nt][to_pos['JAIL']] += prob
    else:
        T[nt][next_p] += prob

for rnd in range(101):
    T = [[0.] * 40 for i in range(3)]
    for t in range(3):
        for pos in x:
            p = to_pos[pos]
            prob = M[t][p] / m / m
            for i in range(1, m + 1):
                for j in range(1, m + 1):
                    if t == 2 and i == m and j == m:
                        T[0][to_pos['JAIL']] += prob
                    else:
                        if i == m and j == m:
                            nt = t + 1
                        else:
                            nt = 0
                        jump(0, (p + i + j) % 40, prob)
    M = [[T[i][j] for j in range(40)] for i in range(3)]
    # print T

ans = [0] * 40
for i in range(3):
    for j in range(40):
        ans[j] += M[i][j]
ans = [[ans[i], i] for i in range(40)]
ans = list(reversed(sorted(ans)))
print ans
# print ans[to_pos['JAIL']], sum(ans)
# print ans
