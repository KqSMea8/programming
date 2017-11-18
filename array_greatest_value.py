def cmp_str(a, b):
    '''
    better compare:
    if a == b:
        return 0;
    if a+b > b+a:
        return 1
    else:
        return -1
    '''
    len_a = len(a)
    len_b = len(b)
    if len_a == len_b:
        if a == b:
            return 0
        elif a < b:
            return -1
        else:
            return 1

    short = a if len_a < len_b else b
    long_ = a if len_a > len_b else b
    index = long_.find(short)
    if index == 0:
        if a == short:
            return cmp_str(short, long_[len(short) : ])
        else:
            return cmp_str(long_[len(short) : ], short)
    else:
        if a < b:
            return -1
        else:
            return 1

def toString(array):
    s = ""
    for i in array:
        s += str(i)
    return s

def func(array):
    array.sort(cmp = cmp_str, key = lambda a : str(a), reverse = True)
    return toString(array)
    
def func_(array):
    if len(array) == 1:
        return [array]
    temp = []
    for i in xrange(len(array)):
        left = array[0 : i]
        left.extend(array[i+1 : ])
        ret = func_(left)
        for j in ret:
            j.append(array[i])
            temp.append(j)
    return temp

def func_enum(array):
    permutations = func_(array)
    it = max(permutations, key = lambda i: toString(i))
    return toString(it)

    
array = [56,99, 9998,58,31, 313, 314]

print array

print func_enum(array)
print func(array)
