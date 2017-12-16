def func(arr):
    last = -1
    for i in xrange(len(arr)):
        if arr[i] % 2:
            last += 1
            temp = arr[last]
            arr[last] = arr[i]
            arr[i] = temp

def func2(arr):
    left = 0
    right = len(arr) - 1
    while left < right:
        if arr[left] % 2 == 0:
            while arr[right] % 2 == 0:
                right -= 1
        temp = arr[left]
        arr[left] = arr[right]
        arr[right] = temp
        left += 1
        right -= 1

test = [6,90,0,-2,1,-3, 9,7,8, 97]

print test
func2(test)
print test


