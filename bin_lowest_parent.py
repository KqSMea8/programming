def in_tree(T, n):
    if T:
        if T == n:
            return True
        if in_tree(T.left, n):
            return True
        return in_tree(T.right, n)
    else:
        return False

def func(T, n1, n2):
    if T:
        left1 = in_tree(T.left, n1)
        right1 = in_tree(T.right, n1)
        left2 = in_tree(T.left, n2)
        right2 = in_tree(T.right, n2)
        if (not left1 and not right1) or (not left2 and not right2):
            return None
        elif (left1 and right2) or (right1 and left2):
            return T
        else:
            child = None
            if left1:
                child = T.left
            else:
                child = T.right
            if child == n1 or child == n2:
                return T
            else:
                return func(child, n1, n2)
    else:
        return None
