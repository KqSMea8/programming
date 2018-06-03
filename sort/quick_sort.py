# sort arr[start, end)
def quick_sort(arr, start, end):
    if end - start <= 1:
        return
    pivot = arr[start]
    last = start
    for i in xrange(start+1, end):
        if arr[i] < pivot:
            last += 1
            arr[last], arr[i] = arr[i], arr[last]
    temp = arr[last]
    arr[last] = pivot
    arr[start] = temp
    quick_sort(arr, start, last)
    quick_sort(arr, last+1, end)

if __name__ == "__main__":
    test = [5, 7, 90, -9]
    quick_sort(test, 0, len(test))
    print test
