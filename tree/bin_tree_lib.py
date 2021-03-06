#-*- coding: utf-8 -*-
import collections

class Node:
    def __init__(self, data):
        self.left = None
        self.right = None
        self.data = data

#先序建立二叉树，以负数表示空子树
def build_bin_tree():
    v = int(input())
    if v < 0:
        return None
    root = Node(v)
    root.left = build_bin_tree()
    root.right = build_bin_tree()
    return root

def bin_tree_deepth(T):
    if not T:
        return 0
    deepl = func(T.left)
    deepr = func(T.right)
    deep = deepl if deepl > deepr else deepr
    return deep + 1

def print_n_layer(Tree, n):
    if Tree == None or n < 0:
        return 0
    if n == 0:
        print Tree.data,
        return 1
    left = print_n_layer(Tree.left, n - 1)
    right = print_n_layer(Tree.right, n - 1)
    return left or right

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

def middle_traverse_non_recursive(Tree):
    stack = collections.deque()
    p = Tree
    while p or len(stack):
        while p:
            stack.append(p)
            p = p.left
        if len(stack):
            p = stack.pop()
            print p.data
            p = p.right

def post_traverse_non_recursive(Tree):
    stack1 = collections.deque()
    stack2 = collections.deque()
    p = Tree

    while p or len(stack1):
        flag = (p == None)

        while p:
            stack1.append(p)
            p = p.left

        if flag:
            while len(stack2):
                q = stack2.pop()
                if q[1] == len(stack1):
                    print q[0].data
                else:
                    stack2.append(q)
                    break


        if len(stack1):
            p = stack1.pop()
            stack2.append((p, len(stack1)))
            p = p.right

    while len(stack2):
        q = stack2.pop()
        print q[0].data

    # end "post_traverse_non_recursive"

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
