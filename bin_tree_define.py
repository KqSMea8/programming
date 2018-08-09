#-*- coding: utf-8 -*-

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
