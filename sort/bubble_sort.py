# -*- coding: utf8 -*-
# the best
def bubble_sort(lst):
    lstLen = len(lst)
    #count = 0
    while lstLen >= 2:
        unorder_len = 1 # 剩余未排序长度
        for i in xrange(1, lstLen):
            #count += 1
            if lst[i] < lst[i-1]:
                lst[i],lst[i-1] = lst[i-1],lst[i]
                unorder_len = i
                
        lstLen = unorder_len

    #print "compare:",count

#the better
def bubble_sort_better(lst):
    lstLen = len(lst)
    #count = 0
    Flag = False
    while lstLen >= 2:
        for i in xrange(1, lstLen):
            #count += 1
            if lst[i] < lst[i-1]:
                lst[i],lst[i-1] = lst[i-1],lst[i]
                Flag = True
                
        if Flag:
            Flag = False
        else:
            break
        
        lstLen -= 1

    #print "compare:",count

def bubble_sort_bad(lst):
    lstLen = len(lst)
    #count = 0
    while lstLen >= 2:
        for i in xrange(1, lstLen):
            #count += 1
            if lst[i] < lst[i-1]:
                lst[i],lst[i-1] = lst[i-1],lst[i]
                
        lstLen -= 1

    #print "compare:",count

def isSorted(lst, ascend = True):
    lstLen = len(lst)
    for i in xrange(1,lstLen):
        if ascend and lst[i-1] > lst[i]:
            return False
        if (not ascend) and lst[i-1] < lst[i]:
            return False
    return True
