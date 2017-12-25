def func(matrix):
    d = [[0, 1], [1, 0], [0, -1], [-1, 0]]
    width = len(matrix[0])
    height = len(matrix)
    x, y = 0, -1 
    change_factor = 0
    while width > 0 and height > 0:
        #print "(", width, height, ")"
        #print d[change_factor]
        if d[change_factor][0]:
            r = height
            width -= 1
        else:
            r = width 
            height -= 1

        for i in xrange(r):
            x, y = x + d[change_factor][0], y + d[change_factor][1]
            print x,y, matrix[x][y]

        change_factor += 1
        change_factor %= 4


height = 4
width = 4
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
func(matrix)
