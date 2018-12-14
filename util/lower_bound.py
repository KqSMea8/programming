#l[begin, end)
def lower_bound(l, begin, end, value):
    first = begin
    count = end - begin
    while count > 0:
        mid = first + count // 2
        if l[mid] < value:
            count -= mid - first + 1
            first = mid + 1
        else:
            count = mid - first
    return first

if __name__ == "__main__":
    l = [1, 100, 100, 3001]
    value = 100 
    print(lower_bound(l, 0, len(l), value))
