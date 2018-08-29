#-*-coding: utf-8 -*-
import bin_tree_define
import traverse_bin_tree
import sys

def func(T, v1, v2, result):
    if T:
        l = func(T.left, v1, v2, result)
        if l[0] and l[1]: #都在左子树
            result.append(T.data)
            return l

        r = func(T.right, v1, v2, result)
        if r[0] and r[1]: #都在右子树
            result.append(T.data)
            return r

        if (l[0] or r[0]) and (l[1] or r[1]): #分别在两棵子树中
            result.append(T.data)
            return [True, True]
        return [l[0] or r[0] or (T.data == v1),
                l[1] or r[1] or (T.data == v2)]
    else:
        return [False, False]

if __name__ == "__main__":
    tree = bin_tree_define.build_bin_tree()
    print '-----------'
    traverse_bin_tree.top_to_down_traverse(tree)
    print '-----------'
    result = []
    func(tree, int(sys.argv[1]), int(sys.argv[2]), result)
    if len(result):
        print result[0]
    else:
        print "no common parent"
