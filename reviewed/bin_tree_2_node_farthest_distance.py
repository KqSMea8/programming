from tree import bin_tree_lib

def func(T, trilist):
    '''Binary tree's any 2 nodes' farthest distance.

       trilist indicates left's deepth, right's deepth and farthest distance.
       Before invoking func, trilist's farthest distance trilist[2] must be initialized to 0.
    '''
    if T == None:
        trilist[0] = trilist[1] = 0
        return

    func(T.left, trilist)
    lld = trilist[0]
    lrd = trilist[1]
    func(T.right, trilist)

    # if subtree is null, then subtree's deepth is 0
    one = 1 if T.left else 0
    ld = (lld + one) if (lld > lrd) else (lrd + one)
    one = 1 if T.right else 0
    rd = (trilist[0] + one) if (trilist[0] > trilist[1]) else(trilist[1] + one)

    trilist[0] = ld
    trilist[1] = rd
    distance = ld + rd
    if distance > trilist[2]:
        trilist[2] = distance

    return

if __name__ == "__main__":
    tree = bin_tree_lib.build_bin_tree()
    l = [0, 0, 0]
    func(tree, l)
    print l[2]
