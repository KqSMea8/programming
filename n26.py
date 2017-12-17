def func(n):
    sum_ = 0
    left = 1
    right = 0

    while right <= (n / 2 + 1):
        #print "###",left, right, sum_
        if sum_ < n:
            right += 1
            sum_ += right
        elif sum_ > n:
            sum_ -= left
            left += 1
        else:
            print (left, right )
            right += 1
            sum_ += right

func(30000)
