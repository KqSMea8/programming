#ifndef __QUEUE__
#define __QUEUE__
#include <cassert>

class queue
{
public:
	queue(size_t max)
	{
		assert(max > 0);
		buffer = new int[max + 1];
		buff_len = max + 1;
		front__ = rear = 0;
	}
	~queue()
	{
		delete[] buffer;
	}
	void push(int v) noexcept
	{
		if (full())
		{
			return;
		}
		buffer[rear] = v;
		rear = (rear + 1) % buff_len;
	}
	void pop() noexcept
	{
		if (empyt())
		{
			return;
		}
		front__ = (front__ + 1) % buff_len;
	}
	bool empyt() const noexcept
	{
		return front__ == rear;
	}
	bool full() const noexcept
	{
		return (rear + 1) % buff_len == front__;
	}
	int back() const noexcept
	{
		int back_index = (rear - 1 + buff_len) % buff_len;
		return buffer[back_index];
	}
	int front() const noexcept
	{
		return buffer[front__];
	}

private:
	size_t front__, rear, buff_len;
	int *buffer;
};
#endif