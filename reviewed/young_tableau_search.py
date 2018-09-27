# -*- coding: utf8 -*-

class Point:
    def __init__(self, r, c):
        self.row = r
        self.col = c
    def __str__(self):
        return "Point[{0},{1}]".format(self.row, self.col)

#获取一个矩阵的元素个数
def count(p1, p2):
    return (p2.row - p1.row + 1) * (p2.col - p1.col + 1)

def get_middle(p1, p2):
    cnt = count(p1, p2)
    mid = cnt / 2
    for i in xrange(p1.row, p2.row + 1):
        for j in xrange(p1.col, p2.col + 1):
            if mid == 0:
                return Point(i,j)
            else:
                mid -= 1


def not_empty(top, bottom, p1, p2):
    return (bottom.row >= p2.row >= p1.row >= top.row) \
                          and (bottom.col >= p2.col >= p1.col >= top.col)

def young_tableau_search(matrix, p1, p2, target):
    cnt = count(p1, p2)
    if cnt == 1:
        return matrix[p1.row][p1.col] ==  target
    mid = get_middle(p1, p2)
    v = matrix[mid.row][mid.col]
    l = []
    if v == target:
        return True
    elif v < target:
        right1 = Point(p1.row, mid.col + 1)
        right2 = p2
        if not_empty(p1, p2, right1, right2):
            l.append([right1, right2])
        bottom1 = Point(mid.row + 1, p1.col)
        bottom2 = Point(p2.row, mid.col)
        if not_empty(p1, p2, bottom1, bottom2):
            l.append([bottom1, bottom2])
    else:
        left1 = p1
        left2 = Point(p2.row, mid.col - 1)
        if not_empty(p1, p2, left1, left2):
            l.append([left1, left2])
        top1 = Point(p1.row, mid.col)
        top2 = Point(mid.row - 1, p2.col)
        if not_empty(p1, p2, top1, top2):
            l.append([top1, top2])

    for i in l:
        if young_tableau_search(matrix, i[0], i[1], target):
            return True

    return False
    


if __name__ == "__main__":
    test = [
         [1, 2, 8, 9],
         [2, 4, 9, 12],
         [4, 7, 10, 13],
         [6, 8, 11, 15]]
    v = 5

    row_count = len(test)
    col_count = len(test[0])
    p1 = Point(0, 0)
    p2 = Point(row_count - 1, col_count - 1)
    print young_tableau_search(test, p1, p2, v)
