#include <iostream>

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
