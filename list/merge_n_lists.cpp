#include <iostream>
#include <queue>
#include <vector>
/*
�ϲ�����
��N�����򣨴�С��������ϲ���һ���µ���������
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
������
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
			if (!lists[i]) // lists[i]�ѱ���ȫ�ϲ�
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
        //���ϲ�������ǰ��һ��λ��
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

/*��С�ѷ�
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

/*��������
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
    
    // N�������ǿ�����
    if (i == n)
    {
        return nullptr;
    }
    
    //�Ե�i������Ϊ������ʼ�ϲ�
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
            if (!pre) // �������ÿ������ֻ�ᷢ��һ�Σ������ǵ�һ���ڵ�
            {
                p->next = head;
                head = p;
                begin = p;
            }
	    else
	    {
	        if (!begin) // ����������ҵ�β��
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
