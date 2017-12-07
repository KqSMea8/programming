def qsort(arr, start, end):
    if end - start <= 1:
        return
    pivot = arr[start]
    last = start
    for i in xrange(start+1, end):
        if arr[i] < pivot:
            last += 1
            temp = arr[last]
            arr[last] = arr[i]
            arr[i] = temp
    temp = arr[last]
    arr[last] = pivot
    arr[start] = temp
    qsort(arr, start, last)
    qsort(arr, last+1, end)

def func_qsort(arr, start, end, k):
    if end - start <= k:
        for i in xrange(start, end):
            print arr[i],
        return
    # sorting......
    pivot = arr[start]
    last = start
    for i in xrange(start+1, end):
        if arr[i] < pivot:
            last += 1
            temp = arr[last]
            arr[last] = arr[i]
            arr[i] = temp
    temp = arr[last]
    arr[last] = pivot
    arr[start] = temp

    small = last - start
    if small <= k:
        for i in xrange(start, last):
            print arr[i],
    if small < k:
        print arr[last],
        func_qsort(arr, last + 1, end, k - small - 1)
    if small > k:
        func_qsort(arr, start, last, k)

def pre_traverse(tree):
    if tree:
        print tree.data
        pre_traverse(tree.left)
        pre_traverse(tree.right)

class Node:
    pass

class big_heap:
    def __init__(self, k_):
        self.count = 0
        self.root = None
        self.k = k_

    def __str__(self):
        pre_traverse(self.root)
        return ""

    def insert(self, data):
        if self.count < k:
            node = Node()
            node.data = data
            node.left = None
            node.right = None
            self.count += 1

            if self.count == 1:
                self.root = node
                return
            p = self.root
            while True:
                if p.data >= node.data:
                    if p.right == None:
                        p.right = node
                        break
                    else:
                        p = p.right
                else:
                    p.data, node.data = node.data, p.data
                    if p.left:
                        p = p.left
                    else:
                        p.left = node
                        break

        else:
            if data >= self.root.data:
                return
            self.root.data = data
            #readjust heap
            
            p = self.root
            while True:
                big = p
                if p.left and p.left.data > big.data:
                    big = p.left
                if p.right and p.right.data > big.data:
                    big = p.right
                if big == p:
                    break
                p.data, big.data = big.data, p.data
                p = big

def func_heap(arr, k):
    heap = big_heap(k)
    for i in arr:
        heap.insert(i)
    print heap

test = [
        [1,2,3,4,5,6],
        [1],
        [6,5,4,3,2,1],
        [5,8,0,-2,99,100,8,50]
        ]

a = test[3][:]
qsort(a, 0, len(a))
print a
k = 3
func_heap(test[3], k)
func_qsort(test[3], 0, len(test[3]), k)
