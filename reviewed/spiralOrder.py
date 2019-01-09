def func(matrix):
    height = len(matrix)
    if height == 0: return []
    d = [[0, 1], [1, 0], [0, -1], [-1, 0]]
    width = len(matrix[0])
    x, y = 0, -1 
    change_factor = 0
    l = []
    while width > 0 and height > 0:
        if d[change_factor][0]:
            r = height
            width -= 1
        else:
            r = width 
            height -= 1

        for i in xrange(r):
            x, y = x + d[change_factor][0], y + d[change_factor][1]
            l.append(matrix[x][y])

        change_factor += 1
        change_factor %= 4

    return l


height = 2
width = 3
matrix = []
e = 1
for i in xrange(height):
    l = []
    for j in xrange(width):
        l.append(e)
        e += 1
    matrix.append(l)
for i in matrix:
    print i
print func(matrix)
