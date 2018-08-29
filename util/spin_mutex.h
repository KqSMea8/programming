#ifndef __SPIN_MUTEX__
#define __SPIN_MUTEX__
#include <atomic>

class spin_mutex {
	std::atomic_flag flag;
public:
	spin_mutex()
	{
		flag.clear(std::memory_order_relaxed);
	}
	/*
	atomic_flag(const atomic_flag&) = delete;
	atomic_flag& operator=( const atomic_flag& ) = delete;
	因此不需要显示声明non-copyable
	spin_mutex(const spin_mutex&) = delete;
	spin_mutex& operator= (const spin_mutex&) = delete;
	*/
	void lock() {
		while (flag.test_and_set(std::memory_order_acquire))
			;
	}
	void unlock() {
		flag.clear(std::memory_order_release);
	}
};
#endif