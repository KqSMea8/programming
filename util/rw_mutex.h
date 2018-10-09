#ifndef __RW_MUTEX__
#define __RW_MUTEX__

/*
* NEVER use it, just for fun.
*/
#include <mutex>
#include <condition_variable>

class rw_mutex
{
public:
	void lock()
	{
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck, [this]() { return this->flag == 0; });
		flag = -1;
	}
	void unlock()
	{
		std::lock_guard<std::mutex> lck(mtx);
		flag = 0;
		cv.notify_all();
	}
	void lock_shared()
	{
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck, [this]() { return this->flag >= 0; });
		flag++;
	}
	void unlock_shared()
	{
		std::lock_guard<std::mutex> lck(mtx);
		flag--;
		cv.notify_all();
	}
	rw_mutex()
	{
		flag = 0;
	}
private:
	int flag;
	std::condition_variable cv;
	std::mutex mtx;
};
#endif