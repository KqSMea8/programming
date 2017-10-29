import copy

def lcs(str1, str2):
    common = {}
    for i in str2:
        temp = copy.deepcopy(common)
        for j in temp:
            index = str1.find(i, common[j]+1)
            if index >= 0:
                common[j+i] = index
        index = str1.find(i)
        if index >= 0:
            common[i] = index

    keys = common.keys()
    keys = sorted(keys, key = lambda s: len(s), reverse = True)
    return keys[0]

s1 = "ABCDSTYUWCWCCTQMXFBC"
s2 = "ABCCFCDMYIQAB"

print s1
print s2
print lcs(s1, s2)

