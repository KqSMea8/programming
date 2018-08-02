#include <iostream>
#include <queue>

/*
  �ֵ�����:
  ���һ�㷨������rootΪ���Ķ����������нڵ��sibling
  ָ����ͬ���ұߵĽڵ㡣���û���ҽڵ㣬sibling�ÿա�
*/
struct Node {
	Node *left;
	Node *right;
	Node * sibling;
	int value;
};

// ǰ����������
void createTree(Node *&root) {
	int x;
	std::cin >> x;
	if (x == 0)
		root = nullptr;
	else {
		root = new Node;
		root->sibling = nullptr;
		root->value = x;
		createTree(root->left);
		createTree(root->right);
	}
}

void printTree(const Node *root) {
	if (root) {
		if (root->sibling)
		{
			std::cout << "(" << root->value << "->" << root->sibling->value << ")";
		}
		else
		{
			std::cout << "(" << root->value << ")";
		}
		printTree(root->left);
		printTree(root->right);
	}
}

/*
ʹ�ö��н��й����������
*/
Node *Connect(Node *root) {
	if (!root) {
		return root;
	}
	std::queue<Node *> level;
	Node *level_start;
	Node *pre, *next;

	level.push(root);
	level_start = root;
	pre = nullptr;

	while (!level.empty()) {
		next = level.front();
		level.pop();
		if (next == level_start) {
			level_start = NULL; // û��ǰ��
		}
		else
		{
			pre->sibling = next;
		}

		if (next->left) {
			if (!level_start) {
				level_start = next->left;
			}
			level.push(next->left);
		}
		if (next->right) {
			if (!level_start) {
				level_start = next->right;
			}
			level.push(next->right);
		}
		pre = next;
	}
	return root;
}

int main() {
	Node *root;
	createTree(root);
	printTree(root);
	Connect(root);
	std::cout << '\n';
	printTree(root);
	return 0;
}