def func(s1, s2):
    a = []
    for i in xrange(128):
        a.append(0)
    for i in s2:
        a[ord(i)] = 1
    """
    pFast, pSlow
    """
    s = ""
    for i in s1:
        if a[ord(i)] == 0:
            s += i
    return s

s1 = "They are students."
s2 = "aeiou"
print func(s1, s2)
