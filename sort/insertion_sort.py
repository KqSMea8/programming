def func(l):
    l_len = len(l)
    for i in xrange(1, l_len):
        insert_pos = -1 
        for j in xrange(i-1, -1, -1):
	    if l[i] >= l[j]:
	        insert_pos = j + 1
	        break
        else:
            # l[i] is the min
            insert_pos = 0
        if insert_pos == i:
            continue
        temp = l[i]
        for j in xrange(i, insert_pos, -1):
            l[j] = l[j-1]
        #insert
        l[insert_pos] = temp

