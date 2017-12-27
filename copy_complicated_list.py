### http://zhedahht.blog.163.com/blog/static/254111742010819104710337/
class cl:
    def __init__(self, v):
        self.data = v
        self.next = None
        self.sibling = None


def print_cl(head):
    p = head
    while p:
        print p.data,
        if p.sibling:
            print p.sibling.data
        else:
            print "None"
        p = p.next

def func(head):
    if not head:
        return None
    p = head
    while p:
        q = p.next
        node = cl(p.data)
        p.next = node
        node.next = q
        p = q
    ret = head.next

    p = head
    while p:
        q = p.next.next
        if p.sibling:
            p.next.sibling = p.sibling.next
        p = q
    p = head
    while p.next:
        q = p.next
        p.next = q.next
        p = q
    return ret


a = cl(1)
b = cl(2)
c = cl(3)
d = cl(4)
e = cl(5)

a.next = b
a.sibling = c
b.next = c
b.sibling = e
c.next = d
d.next = e
d.sibling = b

print_cl(a)
print
n_a = func(a)
print_cl(a)
print
print_cl(n_a)

