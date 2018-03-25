#include<iostream>

using namespace std;

struct node {
  node *next;
  int v;
  node(int v) { this->v = v;this->next = NULL;}
};

void print(const node *head) {
  while (head) {
    cout <<  head->v << endl;
    head = head->next;
  }
}

node *revert(node *head) {
  /* ---iterate---
  node*pre, *p, *post;

  if (!p) {
    return p;
  }
  pre = NULL;
  p = head;
  while (p->next) {
    post = p->next;
    p->next = pre;
    pre = p;
    p = post;
  }
  p->next = pre;
  return p;
  */

  // recursive
  node *next, *new_head;
  if (!head || !(head->next)) {
    return head;
  }
  next = head->next;
  head->next = NULL;
  new_head = revert(next);
  next->next = head;
  return new_head;

  
}

int main() {
  node *head = new node(1);
  node n2(2);
  node n3(3);
  head->next = &n2;
  n2.next = &n3;

  head = revert(head);
  print(head);

  return 0;
}
