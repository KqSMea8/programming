#include <thread>
#include <atomic>
#include <cassert>

std::atomic<bool> ready{ false };
int data = 0;
void producer()
{
	data = 100;                                       // A
	//no reads or writes in the current thread can be reordered after this store.
	ready.store(true, std::memory_order_release);     // B
}
void consumer()
{
	//no reads or writes in the current thread can be reordered before this load.
	while (!ready.load(std::memory_order_acquire))    // C
		;
	assert(data == 100); // never failed              // D
}
int main()
{
	std::thread t1(producer);
	std::thread t2(consumer);
	t1.join();
	t2.join();
	return 0;
}