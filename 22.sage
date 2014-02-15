with open("names.txt", "r") as fin :
    x = sorted(eval(fin.readline()))
print sum([idx * sum([ord(i) - ord('A') + 1 for i in S]) for idx, S in enumerate(x, 1)])
