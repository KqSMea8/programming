# -*- coding:utf-8 -*-

def func(seq): # 连续
    if len(seq) == 0:
        return 0
    max_len = 1
    current_len = 1
    for i in xrange(1, len(seq)):
            if seq[i] >= seq[i - 1]:
                current_len += 1
            else:
                if current_len > max_len:
                    max_len = current_len
                current_len = 1
    if current_len > max_len:
        max_len = current_len
    return max_len

def func_ex(seq): # 非连续
    if len(seq) == 0:
        return 0
    len_ = [1] # the first elem's len is 1
    max_len = 1
    for i in xrange(1, len(seq)):
        current_len = 0
        for j in xrange(0, i):
            if seq[j] <= seq[i] and len_[j] > current_len:
                current_len = len_[j]
        current_len += 1
        if current_len > max_len:
            max_len = current_len
        len_.append(current_len)
    return max_len

test = [5, 3, 4, 8, 6, 7];   

print func_ex(test)

