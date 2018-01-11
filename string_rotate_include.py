def func(s1, s2):
    l1 = len(s1)
    l2 = len(s2)
    if l1 < l2:
        return False
    for i in xrange(l1):
        if s1[i] != s2[0]:
            continue
        p = i + 1
        for j in xrange(1, l2):
            if p >= l1:
                p = 0
            if s1[p] != s2[j]:
                break
            p += 1
        else:
            return True
    return False

s1 = "AABCD"
s2 = "CDAA"

s1 = "ABCD"
s2 = "ACBD"
print func(s1, s2)

