#http://zhedahht.blog.163.com/blog/static/2541117420116135376632/
def max_diff1(array):
    arr_len = len(array)
    if arr_len == 1:
        return {"max_diff" : None, "max" : array[0], "min" : array[0]}
    if arr_len == 2:
        return {"max_diff" : array[0]-array[1], "max" : max(array), "min" : min(array)}
    if arr_len == 3:
        d = {"max_diff" : array[0]-array[1], "max" : max(array), "min" : min(array)}
        if array[0]-array[2] > d["max_diff"]:
            d["max_diff"] = array[0]-array[2]
        if array[1]-array[2] > d["max_diff"]:
            d["max_diff"] = array[1]-array[2]
        return d
    
    d_left = max_diff1(array[0 : arr_len / 2])
    d_right = max_diff1(array[arr_len /2 : ])
    d_ret = {}
    d_ret["max_diff"] = max(d_left["max"] - d_right["min"], d_left["max_diff"], d_right["max_diff"])
    d_ret["max"] = max(d_left["max"], d_right["max"]);
    d_ret["min"] = min(d_left["min"], d_right["min"]);

    return d_ret

def max_diff2(array):
    sum = array[0] - array[1]
    max = sum
    for i in xrange(1, len(array)-1):
        a = array[i] - array[i+1]
        temp = sum + a
        sum = temp if temp > a else a
        if max < sum:
            max = sum
    return max

def max_diff3(array):
    max_v = array[0]
    max_diff = array[0] - array[1]
    for i in xrange(1, len(array)):
        if max_v - array[i] > max_diff:
            max_diff = max_v - array[i]
        if array[i] > max_v:
            max_v = array[i]
    return max_diff

test = [ [2, 4, 1, 16, 7, 5, 11, 9],
         [3,6],
         [2,7, -1],
         [2,7,-1,-90, 1000, 2, 200, -9],
         [-1,-2,-3,-9,-8,-7,-6,-5,-1,-100]
         ]

for i in test:
    print i
    print max_diff1(i)
    print max_diff2(i)
    print max_diff3(i)
    print "####################"
    print
