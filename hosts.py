import itertools

alpha = "abcdefghigklmnopqrstuvwxyz"
num = "0123456789"

ab = [i for i in itertools.permutations(alpha, 2)]
aabb = []
for i in ab:
    aabb.append(i[0] + i[0] + i[1] + i[1])

#two_digit_list = [i for i in itertools.product(num, repeat = 2)]
#two_digit_list = [i[0] + i[1] for i in two_digit_list]

sites = set()
for i in aabb:
#for j in two_digit_list:
#sites.add(i + j + ".com")
    for j in num:
        sites.add(i + j * 2 + ".com")

sites.add("qza123.com")
sites.add("www.xvideos.com")
sites.add("ero-video.com")
sites.add("ero-video.net")
sites.add("27bao.com")
sites.add("www.27baola.net")
sites.add("svipshipin.com")
sites.add("aikanfuli.info")
sites.add("www.aikanfuli.info")
sites.add("weibo.com")
sites.add("www.weibo.com")
sites.add("weibo.cn")
sites.add("dgbyg103.com")
sites.add("dgbyg104.com")
sites.add("www.weibo.cn")

n_length_digit_list = []
max_len = 2 # configible
for i in range(1, max_len + 1):
    temp = []
    for j in itertools.product(num, repeat = i):
        s = ""
        for ch in j:
            s += ch
        temp.append(s)
    n_length_digit_list.extend(temp)



for i in n_length_digit_list :
    sites.add("dyby" + i + ".com")
    sites.add("dgby" + i + ".com")
    sites.add("dgbyg" + i + ".com")

sites = list(sites)
sites.sort()
for i in sites:
    print "127.0.0.1 " + i
