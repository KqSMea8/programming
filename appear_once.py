def appear_once_1(array):
    it = 0
    for i in array:
        it ^= i

    return it

def appear_once_2(array):
    it = 0
    for i in array:
        it ^= i
    for i in xrange(len(array)-1):
        another = it ^ array[i]
        if another in array[i+1 : ]:
            return (array[i], another)
    return None

def appear_once_2_good(array):
    it = 0
    for i in array:
        it ^= i
    N = -1 
    while it:
        N += 1
        if it & 1:
            break
        it >>= 1
    mask = 1
    mask <<= N
    it1 = 0
    it2 = 0
    a = []
    b = []
    for i in array:
        if i & mask:
            it1 ^= i
            a.append(i)
        else:
            it2 ^= i
            b.append(i)
    print array
    print a
    print b
    return (it1, it2)

        
def appear_once(array):
    temp = []
    for i in array:
        if i in temp:
            temp.remove(i)
        else:
            temp.append(i)
    return temp


test = [
        [9,7,0,-2, 9,6,5,5,7,6,0,10],
        ]

for i in test:
    print appear_once_2_good(i)
    
