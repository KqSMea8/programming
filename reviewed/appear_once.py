def appear_once_1(array):
    it = 0
    for i in array:
        it ^= i

    return it

def appear_once_2(array):
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
    for i in array:
        if i & mask:
            it1 ^= i
        else:
            it2 ^= i

    return (it1, it2)

        
test = [
        [9,7,0,-2, 9,6,5,5,7,6,0,10],
        ]

for i in test:
    print appear_once_2(i)
    
