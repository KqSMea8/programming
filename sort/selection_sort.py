def selection_sort(l):
    l_len = len(l)
    for i in xrange(l_len - 1):
        min_index = i
        for j in xrange(i+1, l_len):
	    if l[min_index] > l[j]:
	        min_index = j

        if min_index != i:
            # swap
	    l[min_index], l[i] = l[i], l[min_index]
