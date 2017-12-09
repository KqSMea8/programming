def func(l, start, end):
    print l[start : end]
    if end - start <= 1:
        return True
    small = True
    small_end = start
    root = l[end - 1]
    for i in xrange(start, end - 1):
        if small:
            if l[i] > root:
                small = False
                small_end = i
        else:
            if l[i] <= root:
                return False

    res = func(l, start, small_end)
    if res == False:
        return False
    res = func(l, small_end, end - 1)

    return res

test = [5,7,6,9,11,10,8]
print func(test, 0, len(test))

