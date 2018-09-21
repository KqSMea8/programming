def func(matrix):
    height = len(matrix)
    width  = len(matrix[0])

    def func_print(h, w):
        while h >= 0 and w < width:
            print matrix[h][w],
            h -= 1
            w += 1
        return

    for i in xrange(height):
        h, w = i, 0
        func_print(h, w)

    for i in xrange(1, width):
        h, w = height - 1, i
        func_print(h, w)

test = [
        [[1, 2, 3, 4],
         [5, 6, 7, 8],
         [9, 10, 11, 12]],

        [[1, 2, 3, 4, 5]],

        [[1],
         [2],
         [3],
         [4],
         [5]],

        
        [[1, 2, 3, 4],
         [5, 6, 7, 8],
         [9, 10, 11, 12],
         [13, 14, 15, 16]],

        [[1]],

        [[1, 2],
         [3, 4],
         [5, 6],
         [7, 8]],
        ]

for i in test:
    print i
    func(i)
    print
