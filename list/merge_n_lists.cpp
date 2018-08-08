#include <iostream>
#include <queue>
#include <vector>
/*
合并链表：
把N个有序（从小到大）链表合并成一个新的有序链表
*/
struct Node {
	Node *next;
	int value;
};

Node * createList() {
	int value;
	Node *head, *next, *p;	
    head = p = nullptr;
	std::cin >> value;
	while (value >= 0) {
		next = new Node;
		next->next = nullptr;
		next->value = value;
		if (!p)
		{
			p = head = next;
		}
		else
		{
			p->next = next;
			p = p->next;
		}

		std::cin >> value;
	}
	return head;
}

void printList(const Node *head) {
	while (head) {
		std::cout << head->value << " ";
		head = head->next;
	}
	std::cout << '\n';
}

/*
蛮力法
*/
Node *merge(int n, Node* lists[]) {
	Node *head, *pre;
	int next_;
	head = pre = nullptr;
	while (1)
	{
		// find next node
		next_ = 0;
		for (int i = 1; i < n; i++)
		{
			if (!lists[i]) // lists[i]已被完全合并
			{
				continue;
			}
			if (!lists[next_])
			{
				next_ = i;
			}
			else
			{
				if (lists[i]->value < lists[next_]->value)
					next_ = i;
			}
		}
		if (!pre)
		{
			pre = head = lists[next_];
		}
		else
		{
			pre->next = lists[next_];
			pre = pre->next;
		}
		if (!lists[next_]) // finished
			break;
        //被合并的链表前进一个位置
		lists[next_] = lists[next_]->next;		
	}
	return head;
}

struct cmp
{
	bool operator()(const Node* a, const Node* b)
	{
		return a->value > b->value;
	}
};

/*最小堆法
*/
Node* merge_heap(int n, Node* lists[])
{
	if (n == 0) return nullptr;
    std::priority_queue<Node*, std::vector<Node*>, cmp> heap;
	for (int i = 0; i < n; ++i)
	{
		heap.push(lists[i]);
	}
 
	Node* newHead=nullptr;
	Node* p=nullptr;
	Node* q=nullptr;
	while (!heap.empty())
	{
		q = heap.top();
		heap.pop();
		if (q->next != nullptr)    heap.push(q->next);
		if (newHead == nullptr)
		{ 
			newHead = q;
			p = q;
		}
		else
		{
			p->next = q;
			p = p->next;
		}
	}
	return newHead;
}

/*插入排序法
*/
Node *merge_insertion(int n, Node* lists[]) {
    Node *head;
    int i;
    for (i = 0; i < n; i++)
    {
        if (lists[i])
        {
            head = lists[i];
            break;
        }
    }
    
    // N个链表都是空链表
    if (i == n)
    {
        return nullptr;
    }
    
    //以第i个链表为基础开始合并
    for (; ++i < n;)
    {
        Node *begin = head;
        Node *pre = nullptr;
        for (Node *p = lists[i]; p;)
        {
            while (begin)
            {
                if (begin->value <= p->value)
                {
                    pre = begin;
                    begin = begin->next;
                }
                else
                {
                    break;
                }
            }
            Node *q = p->next;
            if (!pre) // 这种情况每个链表只会发生一次，而且是第一个节点
            {
                p->next = head;
                head = p;
                begin = p;
            }
	    else
	    {
	        if (!begin) // 将整个链表挂到尾部
            {
                pre->next = p;
                break;
            }
            else
            {
                p->next = begin;
                pre->next = p;
                begin = p;
            }
	    }
	    p = q;
        }
    }
    return head;
        
}
int main() {
	const int length = 2;
	Node *lists[length];
	for (int i = 0; i < length; i++)
	{
		lists[i] = createList();
	}
	printList(merge_insertion(length, lists));
	return 0;
}
