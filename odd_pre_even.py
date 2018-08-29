# -*- coding: utf-8 -*-
'''
调整数组顺序使奇数位于偶数前面
'''
def func(arr):
    '''
    快速排序法
    '''
    last = -1
    for i in xrange(len(arr)):
        if arr[i] % 2:
            last += 1
            arr[last], arr[i] = arr[i], arr[last]

def func2(arr):
    left = 0
    right = len(arr) - 1
    while left < right:
        if arr[left] % 2 == 1:
            left += 1
            continue 
        if arr[right] % 2 == 0:
            right -= 1
            continue
    
        arr[left],arr[right] = arr[right], arr[left]
        left += 1
        right -= 1

test = [5,3,4,4]

print test
func2(test)
print test
