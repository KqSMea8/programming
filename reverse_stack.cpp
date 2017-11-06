#include <iostream>
#include <stack>
#include <cstdlib>

using namespace std;

typedef struct Node_ {
  int data;
  struct Node_ *next;
}Node;

void func(stack<int> &s, Node *head, Node *tail) {
  if (s.empty()) {
    Node *p = head->next;
    while (p) {
      s.push(p->data);
      p = p->next;
    }
    return;
  }

  Node *p = (Node *)malloc(sizeof(Node));
  p->data = s.top();
  p->next = NULL;
  if (tail == NULL) {
    head->next = p;
  } else {
    tail->next = p;
  }
  s.pop();
  func(s, head, p);
  free(p);
}

int func_1(stack<int> &s, int v, int layer) {
  int top = s.top();
  s.pop();
  if (s.size()+1 == layer) {
    s.push(v);
  } else {
    int ret = func_1(s, v, layer);
    s.push(ret);
  }
  return top;
}

void add_to_bottom(stack<int> &s, int v) {
  if (s.empty()) {
    s.push(v);
  } else {
    int top = s.top();
    s.pop();
    add_to_bottom(s, v);
    s.push(top);
  }
}

void reverse_stack(stack<int> &s) {
  /*
   * 1:
  for (int i = 1; i < s.size();i++) {
    func_1(s, s.top(), i);
  }
  */
  /*
   * 2:
  Node *head = (Node *)malloc(sizeof(Node));
  head->next = NULL;
  func(s, head, NULL);
  */
  if (!s.empty()) {
    int top = s.top();
    s.pop();
    reverse_stack(s);
    add_to_bottom(s, top);
  }
}

int main() {
  stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);
  reverse_stack(s);
  while(!s.empty()) {
    cout << s.top() << endl;
    s.pop();
  }

  return 0;
}

