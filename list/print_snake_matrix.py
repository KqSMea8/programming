# -*- coding: utf8 -*-
'''
蛇形矩阵：
请写一个函数，对于给定的N，打印一个N * N的蛇形矩阵。例如，当N=4时，
1   3   4   10
2   5   9   11
6   8   12   15
7   13   14   16
'''
import sys

def get_diagonal(h, w):
    '''
    while h:
        h -= 1
        w += 1
    return w
    '''
    return h + w

def get_sequence(N, h, w):
    dia = get_diagonal(h, w)
    if dia < N:
        triangle = (dia + 1) * dia / 2
    else:
        triangle = (N + 1) * N / 2
        #            (max  + min) * num / 2       
        triangle += (N - 1 + (N - (dia - (N - 1)) + 1)) * (dia - N) / 2
    '''
    可通过pre控制方向
    '''
#pre = h if (dia % 2) else w
    pre = w if (dia % 2) else h
    if dia >= N:
        pre -= dia - (N - 1)
    return triangle + pre + 1

if __name__ == "__main__":
    N = int(sys.argv[1])
    for i in xrange(N):
        for j in xrange(N):
            print get_sequence(N, i, j), " ",
        print

