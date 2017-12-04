import collections

class Node:
    pass

def top_to_down_traverse(Tree):
    if not Tree:
        return
    queue = collections.deque()
    queue.append(Tree)
    while len(queue):
        temp = queue.popleft()
        print temp.data
        if temp.left:
            queue.append(temp.left)
        if temp.right:
            queue.append(temp.right)

def pre_traverse_non_recursive(Tree):
    stack = collections.deque()
    p = Tree
    while p or len(stack):
        while p:
            print p.data
            """
            needn't push leaf node into stack
            """
            #if (not p.left) and (not p.right): #leaf node
            #    p = None
            #    break;
            stack.append(p)
            p = p.left
        if len(stack):
            p = stack.pop()
            p = p.right


def pre_traverse(Tree):
    if Tree:
        print Tree.data
        pre_traverse(Tree.left)
        pre_traverse(Tree.right)

def middle_traverse(Tree):
    if Tree:
        middle_traverse(Tree.left)
        print Tree.data
        middle_traverse(Tree.right)

def post_traverse(Tree):
    if Tree:
        post_traverse(Tree.left)
        post_traverse(Tree.right)
        print Tree.data

n8 = Node()
n8.data = 8
n8.left = None
n8.right = None

n6 = Node()
n6.data = 6
n6.left = None
n6.right = None

n7 = Node()
n7.data = 7
n7.left = None
n7.right = None

n5 = Node()
n5.data = 5
n5.left = None
n5.right = None

n9 = Node()
n9.data = 9
n9.left = None
n9.right = None

n10 = Node()
n10.data = 10
n10.left = None
n10.right = None

n11 = Node()
n11.data = 11
n11.left = None
n11.right = None

n8.left = n6
n8.right = n10
n6.left = n5
n6.right = n7
n10.left = n9
n10.right = n11

pre_traverse(n8)
print
pre_traverse_non_recursive(n8)
