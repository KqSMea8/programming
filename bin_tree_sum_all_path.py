def func(Tree):
    stack = []
    right_visited = []
    top = -1
    p = Tree
    while p or top >= 0:
        while p:
            top += 1
            if len(stack)-1 >= top:
                stack[top] = p
                right_visited[top] = False
            else:
                stack.append(p)
                right_visited.append(False)

            if (not p.left) and (not p.right): #leaf node
                print "leaf node", p.data
                for i in xrange(top+1):
                    print stack[i].data,
                print

            p = p.left

        while top >= 0 and right_visited[top]:
            top -= 1

        if top >= 0:
            p = stack[top]
            p = p.right
            right_visited[top] = True

