def func_recursive(T):
    if T:
        func_recursive(T.left)
        func_recursive(T.right)
        temp = T.left
        T.left = T.right
        T.right = temp

def func_loop(T):
    import collections
    stack = collections.deque()
    p = T
    while p or len(stack):
        while p:
            temp = p.left
            p.left = p.right
            p.right = temp

            stack.append(p)
            p = p.left
        if len(stack):
            p = stack.pop()
            p = p.right
