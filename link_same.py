##http://www.cnblogs.com/heaad/archive/2010/06/06/1752468.html
import copy


class Point:
    def __str__(this):
        return "Point[{0},{1}]".format(this.x, this.y)
    def __eq__(this, other):
        return (this.x == other.x) and (this.y == other.y)

def link_0(chess, a, b):
    if a.x == b.x:
        for i in xrange(min(a.y, b.y) + 1, max(a.y, b.y)):
            if chess[a.x][i] != 0:
                break
        else:
            return True

    if a.y == b.y:
        for i in xrange(min(a.x, b.x) + 1, max(a.x, b.x)):
            if chess[i][a.y] != 0:
                break
        else:
            return True
    
    return False

def link_1(chess, a, b):
    p = Point()
    p.x, p.y = a.x, b.y
    if chess[p.x][p.y] == 0 and link_0(chess, a, p) and link_0(chess, b, p):
        return True
    
    p.x, p.y = b.x, a.y
    if chess[p.x][p.y] == 0 and link_0(chess, a, p) and link_0(chess, b, p):
        return True
    return False

def link_2(chess, a, b):
    v = [[0,1],
         [0,-1],
         [1, 0],
         [-1, 0] ]
    p = Point()
    for i in v:
        p.x, p.y = a.x, a.y
        while True:
            p.x, p.y = p.x + i[0], p.y + i[1]
            if not ((0 <= p.x <= N-1) and (0 <= p.y <= N-1)):
                break
            if chess[p.x][p.y] != 0:
                break
            if link_1(chess, p, b):
                return True

    return False

def link_same(chess, a, b):
    if link_0(chess, a, b):
        print "0 turn"
        return True
    if link_1(chess, a, b):
        print "1 turn"
        return True
    if link_2(chess, a, b):
        print "2 turn"
        return True
    return False

def prset(s):
    for i in s:
        print i
        
def good(chess, a, b):
    S = [a]
    max_turn = 2
    count = 0;
    while(count <= max_turn):
        T = []
        for i in S:
            v = [[0,1],
                 [0,-1],
                 [1, 0],
                 [-1, 0]]
            
            for j in v:
                p = Point()
                p.x, p.y = i.x, i.y
                while True:
                    p.x, p.y = p.x + j[0], p.y + j[1]
                    if not ((0 <= p.x <= N-1) and (0 <= p.y <= N-1)):
                        break
                    if chess[p.x][p.y] != 0:
                        if p == b:
                            print count, "turn"
                            return True
                        break
                    if not p in T:
                        T.append(copy.deepcopy(p))

        
        for i in T:
            if not i in S:
                S.append(copy.deepcopy(i))

        count += 1

    return False
    


N = 5
chess = [ [1,0,0,0,0],
          [0,0,0,1,0],
          [0,1,1,0,0],
          [1,1,0,1,1],
          [0,0,0,0,0] ]    

a = Point()
a.x = 0
a.y = 0
b = Point()
b.x = 3
b.y = 3

print link_same(chess, b,a)
print good(chess, a,b)
print good(chess, b,a)
