#ifndef __SPIN_MUTEX__
#define __SPIN_MUTEX__
#include <atomic>

#if 0
class spin_mutex {
	std::atomic<bool> used = ATOMIC_VAR_INIT(false);
public:
	spin_mutex() = default;
	spin_mutex(const spin_mutex&) = delete;
	spin_mutex& operator= (const spin_mutex&) = delete;
	void lock()
	{
		/*bool expected = false;
		while (!used.compare_exchange_strong(expected, true, std::memory_order_acq_rel, std::memory_order_relaxed))
		{
			expected = false;
		}*/
		while (used.exchange(true, std::memory_order_acquire))
			;
	}
	void unlock()
	{
		used.store(false, std::memory_order_release);
	}
};

#else

class spin_mutex {
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
	spin_mutex() = default;
	spin_mutex(const spin_mutex&) = delete;
	spin_mutex& operator= (const spin_mutex&) = delete;
	void lock() {
		while (flag.test_and_set(std::memory_order_acquire))
			;
	}
	void unlock() {
		flag.clear(std::memory_order_release);
	}
};
#endif
#endif