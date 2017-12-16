#include <stack>
#include <iostream>
using namespace std;

template<typename T> class CQueue
{
public:
      CQueue() {}
      ~CQueue() {}

      void push(const T& node);
      void pop();
      bool empty() const;
      int size() const;
      T &front();
      T &back();
private:
     stack<T> front_stack;
     stack<T> back_stack;
     void addToButtom(const T& node);
     void deleteButtom();
};


template <typename T> void CQueue<T>::deleteButtom() {
  if (back_stack.size() == 1) {
    back_stack.pop();
  } else {
    T &e = back_stack.top();
    back_stack.pop();
    deleteButtom();
    back_stack.push(e);
  }
}

template <typename T> void CQueue<T>::addToButtom(const T& node) {
  if (front_stack.empty()) {
    front_stack.push(node);
  } else {
    T &e = front_stack.top();
    front_stack.pop();
    addToButtom(node);
    front_stack.push(e);
  }
}

template <typename T> void CQueue<T>::pop() {
  front_stack.pop();
  deleteButtom();
}

template <typename T> void CQueue<T>::push(const T& node) {
  back_stack.push(node);
  addToButtom(node);
}

template <typename T> int CQueue<T>::size() const {
  return front_stack.size();
}

template <typename T> bool CQueue<T>::empty() const {
  return front_stack.empty();
}

template <typename T> T& CQueue<T>::front() {
  return front_stack.top();
}

template <typename T> T& CQueue<T>::back() {
  return back_stack.top();
}

int main() {
  CQueue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  while (q.size()) {
    int f = q.front();
    int b = q.back();
    cout << "front:" << f << ", back:" << b << endl;
    q.pop();
  }
}
