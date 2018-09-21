# -*- coding: utf-8 -*-

#排列
def func(string):
    if len(string) == 1:
        return list(string)

    ret = []
    for i in xrange(len(string)):
        temp = func(string[0:i] + string[i+1:])
        for j in temp:
            ret.append(string[i] + j)
    return ret

#组合
def func_2(string):
    if len(string) == 0:
        return [""]

    c = string[0]
    combination = func_2(string[1:])
    com_len = len(combination)
    for i in xrange(com_len):
        combination.append(c + combination[i])
    return combination

if __name__ == "__main__":
    test = "abc"
    for i in func_2(test):
        print i

