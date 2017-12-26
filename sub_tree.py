from bin_tree_define import Node

def isSub(a, b, c = False):
    if not b:
        return False

    if a:
        if a.data == b.data:
            if (not b.left) and (not b.right):
                return True
            l = True
            r = True
            if b.left:
                if not isSub(a.left, b.left, True):
                    l = False
            if b.right:
                if not isSub(a.right, b.right, True):
                    r = False
            if l and r:
                return True

        else:
            if c:
                return False

        if isSub(a.left, b):
            return True
        return isSub(a.right, b)

    else:
        return False


### a tree
n1 = Node(2)
n2 = Node(8)
n3 = Node(7)
n4 = Node(9)
n5 = Node(2)
n6 = Node(4)
n7 = Node(7)
n1.left = n2
n1.right = n3
n2.left = n4
n2.right = n5
n5.left = n6
n5.right = n7

### b tree
n8 = Node(2)
n9 = Node(4)
n10 = Node(7)
n8.left = n9
n8.right = n10

print isSub(n1, n8)
