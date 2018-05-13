def func(l):
    l_len = len(l)
    # make 'increment sequence'
    incr = [l_len/2, 0, -1]
    if 1 not in incr:
        incr.append(1)

    for i in incr:
        for j in xrange(i): # there are 'i' sub sequences need being sorted
            # begin insertion sorting
            for k in xrange(j+i, l_len, i):
                insert_pos = -1
                for m in xrange(k-i, j-1, -i):
                    if l[k] >= l[m]:
                        insert_pos = m + i
                        break
                else:
                    insert_pos = j
                if insert_pos == k:
                    continue
                temp = l[k]
                for m in xrange(k, insert_pos, -i):
                    l[m] = l[m-i]
                l[insert_pos] = temp






