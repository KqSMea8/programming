#ifndef __PROCESSOR__HEADER__
#define __PROCESSOR__HEADER__
#include <thread>
#include <queue>
#include <condition_variable>
#include <vector>
#include <memory>
#include <iostream>

struct T
{
    T() = default;
    T(int v_):v(v_)
    {
        std::cout << "int constructor" << std::endl;
    }
    T(T &&t)
    {
        v = t.v;
        t.v = -1;
    }
    T(const T&t)
    {
        std::cout << "copy constructor slow..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        v = t.v;
    }
    T&operator=(T &&t)
    {
        v = t.v;
        t.v = -1;
    }
    T&operator=(const T&t)
    {
        std::cout << "copy operator= slow..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        v = t.v;
    }
    int v;
};

struct data_t {
    T type;
    data_t(data_t &&d)
    {
        this->type = std::move(d.type);
    }
    data_t() = default;
    data_t(const data_t &d) = delete;
    data_t &operator=(const data_t &d) = delete;
    data_t &operator=(data_t &&d)
    {
        if (this != &d)
        {
            this->type = std::move(d.type);
        }
        return *this;
    }
};

using data_handle = bool (*)(const data_t&);

class processor
{
public:
    void add_data(data_t &d);
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
