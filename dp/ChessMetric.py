import collections
def move(size, pos):
    l = []
    # 'X' move
    x = [-1, 0, 1]
    for i in x:
        for j in x:
            if i == 0 and j == 0:
                continue
            a, b = pos[0] + i, pos[1] + j
            if 0 <= a < size and 0 <= b < size:
                l.append((a,b))
    # 'L' move
    y = [-1, 1]
    z = [-2, 2]
    for k in range(2):
        for i in y:
            for j in z:
                a, b = pos[0] + i, pos[1] + j
                if 0 <= a < size and 0 <= b < size:
                    l.append((a,b))
        y, z = z, y

    return l
                
def howMany(size, start, end, numMoves):
    counter = collections.Counter({start : 1})
    for i in range(numMoves):
        temp = collections.Counter()
        for j in counter:
            # move from j
            l = move(size, j)
            for k in l:
                temp[k] += counter[j]
        counter = temp

    return counter[end]

if __name__ == "__main__":
    print(howMany(100, (0, 0), (0, 99), 50))

