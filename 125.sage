N = 10^8
x = [i * (i + 1) * (2 * i + 1) / 6 for i in [0 .. int(sqrt(N) * 2)]]

def is_palin(x) :
    x = str(x)
    return list(x) == list(reversed(x))

s = set()
for i in range(len(x)) :
    for j in range(i - 1) :
        if x[i] - x[j] <= N and is_palin(x[i] - x[j]) :
            s.add(x[i] - x[j])

print s, sum(s)
