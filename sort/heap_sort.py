# adjust l[0, length + 1]
def heap_adjust(l, n, length):  
    right = (n + 1) * 2
    left = right - 1
    if left >= length: # leaf node
        return
    if right >= length: # only left child, no right child
        if l[n] < l[left]:
            l[n], l[left] = l[left], l[n]
        return
    # both left and right
    if l[n] >= l[left] and l[n] >= l[right]:
        return
    bigger = left if l[left] > l[right] else right
    l[n], l[bigger] = l[bigger], l[n]
    heap_adjust(l, bigger, length)

def heap_sort(l):
    length = len(l)
    # step 1: build heap
    # there are (length / 2) non-leaf nodes
    for i in xrange( length / 2 - 1, -1, -1):
        heap_adjust(l, i, length)

    # step 2: swap heap vertex and heap tail, then rebuild heap
    while length > 1:
        l[0], l[length - 1] = l[length - 1], l[0]
        length -= 1
        heap_adjust(l, 0, length)


