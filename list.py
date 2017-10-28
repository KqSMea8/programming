import random

class link_list:
    pass

def print_link_list(ll):
    if not ll:
        print "empty list"
        return
    a = ll
    while a:
        print a.data, #id(a),
        a = a.next

    print

def reverse_list(ll):
    if not ll:
        return None
    p = q = ll
    k = p.next
    q.next = None
    while k:
        p = k
        k = p.next
        p.next = q
        q = p
    return p

def reverse_list_recur(ll):
    if ll == None or ll.next == None:
        return ll
    p = ll
    q = p.next
    p.next = None
    ret = reverse_list_recur(q)
    q.next = p
    return ret

def last_k(ll, k):
    pre = ll
    move = ll
    move_reserve = None
    for i in xrange(k):
        if move.next == None:
            return None
        move = move.next
    move_reserve = move
    while True:
        for i in xrange(k):
            if move.next == None:
                for j in xrange(i):
                    pre = pre.next
                return pre
            move = move.next
        pre = move_reserve
        move_reserve = move
def info(n):
    return n+1

def list_factory(n):
    head = None
    pre = None
    for i in xrange(n):
        node = link_list()
        node.next = None
        node.data = info(i)
        if i == 0:
            head = node
            pre = node
        else:
            pre.next = node
            pre = node
    return head
        
def middle_node(ll):
    a = ll
    length = 0
    while a:
        length += 1
        a = a.next
    a = ll
    for i in xrange(length / 2):
        a = a.next
    if a:
        print a.data
    else:
        print "empty list"
        
def middle_node_better(ll):
    if not ll:
        print "empty list"
        return
    p = ll
    q = ll
    p_reserve = p
    n = 1   # try 2, 3, 4...
    while True:
        for i in xrange(n):
            if p.next:
                p = p.next
            else:
                for j in xrange(i/2 + 1):
                    if q.next:
                        q = q.next
                print q.data
                return
        q = p_reserve
        p_reserve = p
        n *= 2

def get_meet(ll):
    if not ll:
        return None
    fast = ll
    slow = ll
    while fast.next and fast.next.next:
        slow = slow.next
        fast = fast.next.next
        if fast == slow:
            return fast
    return None

def isCircle(ll):
    if get_meet(ll):
        return True
    else:
        return False

def get_circle_list(n):
    ll = list_factory(n)
    entry = random.randint(1,n)
    q = ll
    for i in xrange(entry-1):
        q = q.next
    p = ll
    while p.next:
        p = p.next
    p.next = q
    return (ll, q)

def get_entry(cir_ll):
    meet = get_meet(cir_ll)
    p = meet
    q = cir_ll
    while p != q:
        p, q = p.next, q.next
    return p

def get_tail(ll):
    if isCircle(ll):
        entry = get_entry(ll)
        q = entry
        while q.next != entry:
            q = q.next
        return q
    else:
        q = ll
        while q.next:
            q = q.next
        return q
def isCross(l1, l2):
    tail = get_tail(l1)
    #print tail.data
    tail.next = l2
    #print isCircle(tail), "circle"
    if isCircle(tail) and get_entry(tail) == tail:
        return True
    else:
        return False

def get_node(ll, n):
    q = ll
    for i in xrange(n-1):
        q = q.next

    
    return q
        
for i in xrange(1,20):
    b = random.randint(1, 10)
    l1,entry = get_circle_list(b)
    #print_link_list(l1)
    #print entry.data, get_tail(l1).data
    c = random.randint(1, b)
    node = get_node(l1,c)
    #print c, node.data
    #print "###########"
    
    l2 = list_factory(random.randint(1, 19))
    tail = get_tail(l2)
    tail.next = node
    
    print isCross(l2,l1)





























    
    
    
    
