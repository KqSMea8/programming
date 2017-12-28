def func(s):
    if len(s) < 2:
        return 0

    max_len = 0
    p = 0
    current_len = 0
    all_same = True
    for i in xrange(1, len(s)):
        if s[i] == s[p]:
            p -= 1
            current_len += 1
            if current_len > max_len:
                max_len = current_len
            if p == -1:
                p = i
                current_len = 0
        else:
            all_same = False
            if current_len > max_len:
                max_len = current_len
            p = i
            current_len = 0

    if all_same:
        return len(s) / 2 * 2
    return max_len * 2


test = "google"
print test
print func(test)
