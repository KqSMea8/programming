import copy

def lcs(str1, str2):
    common = {}  # 'common' is a dict, key is str1 and str2's common sub-seq, value is the index of sub-seq's last char in str1
    for i in str2:
        temp = copy.deepcopy(common)
        for j in temp:
            index = str1.find(i, common[j]+1)
            if index >= 0:
                common[j+i] = index
        index = str1.find(i)
        if index >= 0:
            common[i] = index

    if not common:
        return ""
    keys = common.keys()
    keys = sorted(keys, key = lambda s: len(s), reverse = True)
    return keys[0]

if __name__ == "__main__":
    s1 = "13456778"
    s2 = "357486782"

    print s1
    print s2
    print 'lcs:',lcs(s1, s2)

