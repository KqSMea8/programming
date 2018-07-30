import random

def random_string(length):
    l = xrange(33, 127)
    r = []
    for i in xrange(length):
        r.append(random.choice(l))

    s = ""
    for i in r:
        s += chr(i)

    return s

if __name__ == "__main__":
    print random_string(0)
    print random_string(9)
    print random_string(21)
    
