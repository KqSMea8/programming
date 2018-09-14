#pragma once
#include <list>
#include <iostream>

/*
设计一个栈结构，满足以下条件：min，push，pop操作的时间复杂度为O(1)
*/

struct min_stack
{
  virtual void pop();
  virtual void push(int v);
  bool empty() const
  {
	  return m_stack.empty();
  }
  int min() const
  {
	  return m_minStack.back();
  }
  void print() const
  {
	  std::cout << "element:";
	  for (auto &i : m_stack)
	  {
		  std::cout << i << " ";
	  }
	  std::cout << "\n";
	  std::cout << "min:";
	  for (auto &i : m_minStack)
	  {
		  std::cout << i << " ";
	  }
	  std::cout << "\n";
  }
  protected:
    std::list<int> m_stack;          // 数据栈
    std::list<int> m_minStack;       // 最小元素栈
};

void min_stack::pop()
{
	if (m_stack.empty())
	{
		throw std::exception("stack is empty");
	}
	m_stack.pop_back();
	m_minStack.pop_back();
}

void min_stack::push(int v)
{
	if (m_stack.empty())
	{
		m_minStack.push_back(v);
	}
	else
	{
		int current_min = m_minStack.back();
		m_minStack.push_back(v < current_min ? v : current_min);
	}
	m_stack.push_back(v);
}

/*
min_stack_space_free能节约空间，但是pop效率稍逊于min_stack。

min_stack-------------------------:
element:-1 1 2 0 2 1 7 2 9
min:-1 -1 -1 -1 -1 -1 -1 -1 -1
min_stack_space_free:
element:-1 1 2 0 2 1 7 2 9
min:-1
*/
struct min_stack_space_free : public min_stack
{
	virtual void pop() override;
	virtual void push(int v) override;
};

void min_stack_space_free::pop()
{
	if (m_stack.empty())
	{
		throw std::exception("stack is empty");
	}
	
	int top = m_stack.back();
	m_stack.pop_back();

	// 判断最小值是不是由‘top’引入，如果是，最小值出栈，否则不出栈

	// 值不相等，肯定不是‘top’引入，不出栈
	if (top != m_minStack.back())
	{
		return;
	}
	for (auto &i : m_stack)
	{
		/*
		最小值由'i'引入，不是'top'引入，不出栈
		*/
		if (i == top)
		{
			return;
		}
	}
	// 最小值由‘top'引入，出栈
	m_minStack.pop_back();
}

void min_stack_space_free::push(int v)
{
  if (m_stack.empty())
  {
    m_minStack.push_back(v);	
  }
  else
  {
	  if (v < m_minStack.back())
	  {
		  m_minStack.push_back(v);
	  }
  }

  m_stack.push_back(v);
}

#if 0
#include <iostream>
#include "min_stack.h"
#include <random>
#include <cassert>

inline int get_random_int(int min, int max)
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(min, max);
	return uniform_dist(e1);
}

int main()
{
	min_stack            s1;
	min_stack_space_free s2;
	int g_c = 10000;

	while (g_c--)
	{
		bool push = get_random_int(0, 3) % 2 ? true : false;
		if (!push && s1.empty())
		{
			push = true;
		}
		int count = get_random_int(1, 100);
		while (count-- > 0)
		{
			if (push)
			{
				int v = get_random_int(-1, 90);
				s1.push(v);
				s2.push(v);
			}
			else
			{
				if (s1.empty())
					break;
				s1.pop();
				s2.pop();
			}
		}
		/*std::cout << "min_stack-------------------------:\n";
		s1.print();
		std::cout << "min_stack_space_free:\n";
		s2.print();*/
		if (!s1.empty())
		{
			assert(s1.min() == s2.min());
		}
	}
	while (!s1.empty())
	{
		assert(s1.min() == s2.min());
		/*std::cout << "min_stack-------------------------:\n";
		s1.print();
		std::cout << "min_stack_space_free:\n";
		s2.print();*/
		s1.pop();
		s2.pop();
	}
	std::cout << "exit";
	getchar();
}
#endif