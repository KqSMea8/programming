def is_ugly(n):
    while n % 2 == 0:
        n /= 2
    while n % 3 == 0:
        n /= 3
    while n % 5 == 0:
        n /= 5
    if n == 1:
        return True
    else:
        return False

def func_enum(n):
    i = 1
    count = 0
    while count != n:
        if is_ugly(i):
            count += 1
        i += 1
    return i - 1

def func_good(n):
    un = [1]
    t2 = 0
    t3 = 0
    t5 = 0
    m = 1
    for i in xrange(1, n):
        m2 = un[t2] * 2
        m3 = un[t3] * 3
        m5 = un[t5] * 5

        if m2 <= m3 and m2 <= m5:
            m = m2
            t2 += 1
        if m3 <= m2 and m3 <= m5:
            m = m3
            t3 += 1
        if m5 <= m2 and m5 <= m3:
            m = m5
            t5 += 1
        un.append(m)
    return un[n - 1]

print func_good(1500)
