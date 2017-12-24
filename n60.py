def isBlanced(t):
    if not t:
        return 0

    dl = isBlanced(t.left)
    if dl == -1: # not blanced
        return -1

    dr = isBlanced(t.right)
    if dr == -1: # not blanced
        return -1

    if abs(dl - dr) > 1:
        return -1

    d = dl if dl > dr else dr
    return d + 1


