#include <iostream>
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

int main() {
	const int length = 3;
	Node *lists[length];
	for (int i = 0; i < length; i++)
	{
		lists[i] = createList();
	}
	printList(merge(length, lists));
	return 0;
}
