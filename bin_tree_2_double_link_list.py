# -*- coding: utf-8 -*-
'''
给出一颗有序二叉树，将它转换为有序的双向链表输出。
有序二叉树形如：
           10
         /    \
        6       14
      /   \    /  \
    4      8  12  16
双向链表形如：
4=6=8=10=12=14=16
'''
import bin_tree_define

def func(T):
    if T:
        func(T.left)
        pre = T.left
        while pre and pre.right:
            pre = pre.right
        T.left = pre
        if pre:
            pre.right = T
        func(T.right)
        post = T.right
        while post and post.left:
            post = post.left
        T.right = post
        if post:
            post.left = T

if __name__ == "__main__":
    tree = bin_tree_define.build_bin_tree()
    func(tree)

    head = tree
    while head and head.left:
        head = head.left
    tail = head
    while head:
        print head.data, " ",
        tail = head
        head = head.right
    print
    while tail:
        print tail.data, " ",
        tail = tail.left
        

