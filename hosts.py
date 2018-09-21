import string_permutation

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

string = "abcdefghigklmnopqrstuvwxyz"
a = func1(string)
for i in xrange(len(a)):
    a.append(a[i][1] + a[i][0])
aa = []
for i in a:
    aa.append(i[0] + i[0] + i[1] + i[1])
b = []
c = "0123456789"
for i in aa:
    for j in c:
        b.append(i + j + j + ".com")
b.append("qza123.com")
b.append("www.xvideos.com")
b.append("ero-video.com")
b.append("ero-video.net")
b.append("dgbyg55.com")
b.append("dgbyg54.com")
b.append("dgbyg53.com")
for i in b:
    print "127.0.0.1 " + i
