def majority(l):
    count = 0
    value = None
    
    for i in l:
        if count == 0:
            count = 1
            value = i
            continue
        if value == i:
            count += 1
        else:
            count -= 1

    if count != 0:
        cnt = l.count(value)
        if cnt >= (len(l) / 2 + 1):
            return value
        else:
            return None
    else:
        return None

if __name__ == "__main__":
    l = [5,6,5,5,7]
    print majority(l)
