def func(a, b):
    if a == b:
        return 0
    len_a = len(a)
    len_b = len(b)
    if len_a == 0:
        return len_b
    if len_b == 0:
        return len_a
    if len_a == 1 and len_b == 1:
        return 1

    shortest = min(len_a, len_b)
    begin = 0
    while begin < shortest:
        if a[begin] == b[begin]:
            begin += 1
        else:
            break
    if begin > 0:
        return func(a[begin:], b[begin:])

    while len_a > 0 and len_b > 0:
        if a[len_a - 1] == b[len_b - 1]:
            len_a -= 1
            len_b -= 1
        else:
            break
    if len_a != len(a):
        return func(a[0:len_a], b[0:len_b])
    # len_a, len_b remain unchanged
    ia = 0
    jb = 0
    longest  = max(len_a, len_b)
    for i in xrange(len_a):
        j = b.find(a[i])
        if j >= 0:
            ia = i
            jb = j
            break
    else:
        return longest
    temp = func(a[0:ia], b[0:jb]) + func(a[ia + 1:], b[jb + 1:])
    return min(temp, longest)
if __name__ == "__main__":
    print func("inten", "execu")
