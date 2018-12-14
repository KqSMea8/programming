# sorted1[b1,e1)
# sorted2[b2,e2)
def set_intersection(sorted1, b1, e1, sorted2, b2, e2):
    l = []
    while (b1 < e1 and b2 < e2):
        a, b = sorted1[b1], sorted2[b2]
        if a < b:
            b1 += 1
        elif a == b:
            l.append(a)
            b1 += 1
            b2 += 1
        else:
            b2 += 1
    return l
