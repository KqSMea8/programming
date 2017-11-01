#include <stack>

struct s{
  void pop();
  void push(const int &v);
  int min() const;
  private:
    std::stack<int> m_stack;
    std::stack<int> m_minStack;
};

void s::pop() {
  m_stack.pop();
  m_minStack.pop();
}

void s::push(const int &v) {
  if (m_stack.empty()) {
    m_minStack.push(v);
  } else {
    int min = m_minStack.top();
    m_minStack.push(min < v ? min : v);
  }
  m_stack.push(v);
}

int s::min() const {
  return m_minStack.top();
}

