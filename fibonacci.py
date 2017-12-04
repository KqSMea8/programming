def fibonacci_seq(n):
    a,b = 1,1

    while n > 1:
        a,b = b, a+b
        n -= 1
    return b
def fibonacci_seq_rec(n):
    if n <= 2:
        return n
    return fibonacci_seq_rec(n-1) + fibonacci_seq_rec(n-2)

for i in xrange(1, 10):
    print i, fibonacci_seq(i), fibonacci_seq_rec(i)
