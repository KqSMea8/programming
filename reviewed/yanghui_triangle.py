def func(n):
    if n <= 0:
        return

    line = [1]
    for i in xrange(n / 2):
        line.append(0)

    for i in xrange(1, n+1):
        cal = i / 2
        for j in xrange(cal, 0, -1):
            line[j] += line[j-1]
        for j in xrange(cal + 1):
            print line[j],
        for j in xrange(i - (cal+1) - 1, -1, -1):
            print line[j],
        print
        if (i % 2) and (1 < i < n) :
            line[cal+1] = line[cal-1]

func(8)

