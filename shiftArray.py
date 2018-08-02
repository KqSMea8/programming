def shiftArray(arr, n):
    len_arr = len(arr)
    n = n % len_arr
    if n == 0:
        return

    temp = arr[0 : len_arr-n]
    head = arr[len_arr-n : ]
    head.extend(temp)
    for i in xrange(len_arr):
        arr[i] = head[i]

def shiftArray_1(arr, n):
    len_arr = len(arr)
    n = n % len_arr
    if n == 0:
        return

    arr.reverse()
    for i in xrange(n / 2):
        temp = arr[i]
        arr[i] = arr[n-1-i]
        arr[n-1-i] = temp
    for i in xrange((len_arr-n) / 2):
        temp = arr[n+i]
        arr[n+i] = arr[len_arr-1-i]
        arr[len_arr-1-i] = temp

def gcd(a, b):
    """
    c = a % b
    while c:
        a,b = b,c
        c = a % b
    return b
    """
    c = max(a, b) - min(a, b)
    while c:
        a, b = min(a, b), c
        c = max(a, b) - min(a, b)
    return b


def shiftArray_2(arr, n):
    len_arr = len(arr)
    n = n % len_arr
    if n == 0:
        return

    loop = gcd(n, len_arr)
    for i in xrange(loop):
        cur = i
        loc = (cur + n) % len_arr
        move = arr[cur]
        reverse = arr[loc]
        while loc != i:
            arr[loc] = move

            cur = loc
            loc = (cur + n) % len_arr
            move = reverse
            reverse = arr[loc]
        arr[loc] = move



test = range(50)
for i in xrange(len(test) + 5):
    temp1 = test[:]
    temp2 = test[:]
    temp3 = test[:]
    shiftArray_2(temp2, i)
    shiftArray_1(temp1, i)
    shiftArray(temp3, i)
    print i, temp1 == temp2 == temp3
