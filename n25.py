def func(n):
    m = 0
    for i in xrange(1, n+1):
        while i:
            if i % 10 == 1:
                m += 1
            i /= 10
    return m
        

d = {"0" : 0,
     "1" : 1,
     "2" : 2,
     "3" : 3,
     "4" : 4,
     "5" : 5,
     "6" : 6,
     "7" : 7,
     "8" : 8,
     "9" : 9}

def func_better(n):
    s = ["0"]
    count = 0
    cur_count = 0
    j = 1
    strl = 1
    while j <= n:
        j += 1
        for i in xrange(strl):
            _sum = d[s[i]] + 1
            if s[i] == "0":
                cur_count += 1
            elif s[i] == "1":
                cur_count -= 1

            if _sum == 10:
                s[i] = "0"
                if i == strl - 1:
                    strl += 1
                    s.append("1")
                    cur_count += 1
            else:
                s[i] = str(_sum)
                break
        count += cur_count

    return count

print func_better(12)
