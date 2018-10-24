import random

def get_ints(a,b,count=-1):
    if count < 0:
        return [random.randint(a,b)]
    ret = []
    for i in xrange(count):
        ret.append(random.randint(a,b))
    return ret

if __name__ == "__main__":
    print get_ints(1, 5, 6)


