#include <iostream>
#include <stack>
#include <cstdlib>

using namespace std;

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
  if (s.size() > 1) {
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

