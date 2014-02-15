ans = 0
with open("sudoku.txt", "r") as fin :
    for _ in range(50) :
        fin.readline()
        x = []
        for i in range(9) :
            x += [list(map(int, list(fin.readline())[:9]))]
        t = sudoku(matrix(x))[0]
        ans += t[0] * 100 + t[1] * 10 + t[2]
print ans
