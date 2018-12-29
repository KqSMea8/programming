def func1(string):
    ln = len(string)
    if ln <= 1:
        return []
    if ln == 2:
        return [string]
    ret = []
    for i in xrange(ln - 1):
        for j in xrange(i + 1, ln):
            ret.append(string[i] + string[j])
    return ret;

def func2(string):
    a = func1(string)
    for i in string:
        a.append(i + i)
    return a

def func3(string):
    a = func1(string)
    for i in xrange(len(a)):
        a.append(a[i][1] + a[i][0])
    return a
    
alpha = "abcdefghigklmnopqrstuvwxyz"
num = "0123456789"
a = func3(alpha)
aa = []
for i in a:
    aa.append(i[0] + i[0] + i[1] + i[1])

b = []
for i in aa:
    for j in num:
        b.append(i + j + j + ".com")

b.append("qza123.com")
b.append("www.xvideos.com")
b.append("ero-video.com")
b.append("ero-video.net")
b.append("27bao.com")
b.append("www.27baola.net")
b.append("svipshipin.com")
b.append("aikanfuli.info")
b.append("weibo.com")
b.append("www.weibo.com")
b.append("weibo.cn")
b.append("www.weibo.cn")

a = func2(num)
for i in xrange(len(a)):
    if a[i][1] == a[i][0]:
        continue
    a.append(a[i][1] + a[i][0])

for i in a:
    b.append("dyby" + i + ".com")
    b.append("dgby" + i + ".com")
    b.append("dgbyg" + i + ".com")

for i in b:
    print "127.0.0.1 " + i
