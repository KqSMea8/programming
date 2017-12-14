def binsearch(arr, start, end, e):
    left = start
    right = end - 1
    middle = (left + right) / 2
    while left <= right:
        if arr[middle] == e:
            return middle
        elif arr[middle] < e:
            left = middle + 1
        else:
            right = middle - 1
        middle = (left + right) / 2

    return -1

def func_binsrch(arr, start, end, sum_):
    for i in xrange(end-1):
        index = binsearch(arr, i+1, end, sum_ - arr[i])
        if index >= 0:
            return (arr[i], arr[index])
    return ()

def func_good(arr, start, end, sum_):
    left = start
    right = end - 1
    while left < right:
        sm = arr[left] + arr[right]
        if sm == sum_:
            return (arr[left], arr[right])
        elif sm < sum_:
            left += 1
        else:
            right -= 1
    return ()

def non_sorted_func(arr, min_, max_, sum_):
    a = []
    for i in xrange(max_ - min_ + 1):
        a.append(0)
    offset = 0 if min_ == 0 else -min_
    for i in arr:
        a[i + offset] += 1
    left = 0
    right = max_ + offset
    sum_ += 2 * offset
    while left < right or (left == right and a[left] > 1):
        sm = left + right
        if sm == sum_:
            return (left - offset, right - offset)
        elif sm < sum_:
            for i in xrange(left + 1, max_ + 1):
                if a[i] > 0:
                    left = i
                    break
            else:
                left = max_ + offset
        else:
            for i in xrange(right - 1, -1, -1):
                if a[i] > 0:
                    right = i
                    break
            else:
                right = 0
    return ()


test = [-1,2,3,5,4,5,9]

print non_sorted_func(test, min(test), max(test), 8)

