##http://blog.csdn.net/ns_code/article/details/20942045
# get all subarrays then find the biggest one 
def sum1(array):
    d = {"max" : array[0], "index":0, "length":1}
    for index in xrange(len(array)):
        for length in xrange(1, len(array)-index+1):
            temp = sum(array[index : index+length])
            if temp > d["max"]:
                d["max"] = temp
                d["index"] = index
                d["length"] = length
    return d

# better than sum1
def sum2(array):
    d = {"max" : array[0], "index":0, "length":1}
    for i in xrange(len(array)):
        cur_sum = 0
        for j in xrange(i, len(array)):
            cur_sum += array[j]
            if cur_sum > d["max"]:
                d["max"] = cur_sum
                d["index"] = i
                d["length"] = j-i+1
    return d
                
# divide and conquer
def sum3(array):
    arr_len = len(array)
    if arr_len == 1:
        return {"max" : array[0]}
    left = array[0 : arr_len/2]
    right = array[arr_len/2 : ]

    middle = array[arr_len/2-1 : arr_len/2+1]
    left_len = len(left) - 1
    right_len = len(right) - 1
    d = {"max" : sum(middle)}
    for i in xrange(left_len+1):
        cur_sum = sum(array[arr_len/2-1-i : arr_len/2-1]) + sum(middle)
        for j in xrange(right_len):
            cur_sum += array[arr_len/2+1+j]
            if cur_sum > d["max"]:
                d["max"] = cur_sum

    d_left = sum3(left)
    d_right = sum3(right)
   
    return max(d_left, d_right, d, key = lambda a : a["max"])

def good(array):
    d = {"max" : array[0], "index":0, "length":1}
    cur_sum = 0
    length = 0
    index = 0
    for i in xrange(len(array)):
        cur_sum += array[i]
        length += 1
        if cur_sum > d["max"]:
            d["max"] = cur_sum
            d["index"] = index
            d["length"] = length
        if cur_sum <= 0:
            cur_sum = 0
            index = i+1
            length = 0
            
    return d

def sum_dp(array):
    sum = array[ : ]
    sum[0] = sum[0]
    max = sum[0]
    for i in xrange(1, len(array)):
        sum[i] = None
    print sum
    for i in xrange(1, len(array)):
        temp = sum[i-1] + array[i]
        sum[i] = temp if temp > array[i] else array[i]
        if max < sum[i]:
            max = sum[i]
        print sum
    return max



test = [
    [-2,-4,-7,-5,-2,-1,-2,-4,-3],
    [-1,-2,-4,-7,-5,-2,-2,-4,-3],
    [2,4,-7,5,2,-1,2,-4,3],
    [2,5,-1],
    [0],
    [1],
    [-2],
    [2,-2,3],
    [1,-2,3,10,-4,7,2,-5],
    [5,2,-2,3],
    [2,4,5] ]
for a in test:
    print a
    print sum1(a)
    print sum2(a)
    print good(a)
    print sum3(a)
    print sum_dp(a)
    print
