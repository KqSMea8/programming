#ifndef __PROCESSOR__HEADER__
#define __PROCESSOR__HEADER__
#include <thread>
#include <queue>
#include <condition_variable>
#include <vector>
#include <memory>

struct data_t {
    int type;
};

using data_handle = bool (*)(const data_t&);

class processor
{
public:
    void add_data(const data_t &d);
    bool start();
    void stop(bool force = false);

    processor(data_handle h, int w = 1) { 
        handle = h;
        workers_num = w;
        running = false;
    }

private:
    volatile bool running;
    int workers_num;
    std::mutex data_mtx;
    std::mutex status_mtx;
    std::condition_variable data_cond;
    std::queue<data_t> data_queue;
    std::vector<std::shared_ptr<std::thread>> workers;
    data_handle handle;

    void thread_func();

    // uncopyable
    processor(const processor &);
    processor &operator=(const processor &);
};
#endif
