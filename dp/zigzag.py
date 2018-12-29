def longestZigZag(sequence):
    size = len(sequence)
    if size < 2:
        return size 

    #(pre_index, size)
    l = [(-1, 1)]
    longest = 1
    for i in range(1, size):
        cur_len = 1
        pre_index = -1
        for index, v in enumerate(l):
            b = False
            if (v[0] == -1 and sequence[i] != sequence[index]):
                b = True
            if v[0] != -1 and (sequence[v[0]] < sequence[index] > sequence[i]
                    or sequence[v[0]] > sequence[index] < sequence[i]):
                b = True

            if b:
                temp = v[1] + 1
                if temp > cur_len:
                    cur_len = temp
                    pre_index = index

        l.append((pre_index, cur_len))
        longest = max(longest, cur_len)

    return longest


if __name__ == "__main__":
    l = [1, 7, 4, 9, 2, 5]
    l = [1, 17, 5, 10, 13, 15, 10, 5, 16, 8]
    l = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    l = [44]
    l = [70, 55, 13, 2, 99, 2, 80, 80, 80, 80, 100, 19, 7, 5, 5, 5, 1000, 32, 32]
    l = [374, 40, 854, 203, 203, 156, 362, 279, 812, 955, 
         600, 947, 978, 46, 100, 953, 670, 862, 568, 188, 
         67, 669, 810, 704, 52, 861, 49, 640, 370, 908, 
         477, 245, 413, 109, 659, 401, 483, 308, 609, 120, 
         249, 22, 176, 279, 23, 22, 617, 462, 459, 244]
    l = [5, 5, 5, 5]
    print(longestZigZag(l))

