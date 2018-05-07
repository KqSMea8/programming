# merge sorted a and b
def merge(a, b):
    c = []
    i = j = 0
    while (i < len(a) and j < len(b)):
        if a[i] < b[j]:
            c.append(a[i])
            i += 1
        else:
            c.append(b[j])
            j += 1
    if len(a) == i: # copy left b into c
        c.extend(b[j:])
    if len(b) == j: # copy left a into c
        c.extend(a[i:])

    return c

def merge_sort(a):
    len_a = len(a)
    if len_a <= 1:
        return
    pre = a[0 : len_a / 2]
    post = a[len_a / 2 :]
    merge_sort(pre)
    merge_sort(post)
    res = merge(pre, post)
    for i in xrange(len_a):
        a[i] = res[i]


