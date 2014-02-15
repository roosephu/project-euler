# block: [start, end, value]

LMT = 10

lx, ly = 1, 1

def merge(x, y) :

seq = [[1, 1, 0]]

while ly <= LMT :
    lx, ly = ly, lx + ly

    # compute [lx + 1, ly]
    
