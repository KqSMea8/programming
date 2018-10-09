# http://zhedahht.blog.163.com/blog/static/2541117420094279426862/
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

def func_1(n):
    s = ["1"]
    l = 1
    while l <= n:
        temp = ""
        for i in s:
            temp += i
        print temp
    
        s_len = len(s)
        for i in xrange(s_len - 1, -1, -1):
            _sum = d[s[i]] + 1
            if _sum == 10:
                s[i] = "0"
                if i == 0:
                    l += 1
                    s.insert(0, "1")
            else:
                s[i] = str(_sum)
                break
    
func_1(5)
