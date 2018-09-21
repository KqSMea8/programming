#include <iostream>
#include "list_lib.h"

Node *revert_recursive(Node *head) {
  Node *next, *new_head;
  if (!head || !(head->next)) {
    return head;
  }
  next = head->next;
  head->next = NULL;
  new_head = revert_recursive(next);
  next->next = head;
  return new_head;
}

Node *revert_iterate(Node *head) {
  Node*pre, *p, *post;

  if (!head) {
    return nullptr;
  }
  pre = nullptr;
  p = head;
  while (p->next) {
    post = p->next;
    p->next = pre;
    pre = p;
    p = post;
  }
  p->next = pre;
  return p;
}

int main() {
  Node *head = createList();
  head = revert_recursive(head);
  head = revert_iterate(head);
  printList(head);
  return 0;
}
