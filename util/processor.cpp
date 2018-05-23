#include "processor.h"

bool processor::start()
{
    std::lock_guard<std::mutex> lck(status_mtx);
    if (running)
    {
        return true;
    }

    running = true;
    for (int i = 0; i < workers_num; i++)
    {
        std::shared_ptr<std::thread> p(new std::thread(std::bind(&processor::thread_func, this)));
        workers.push_back(p);
    }
    return true;
}

void processor::thread_func()
{
    while(1) {
        data_t data;
        {
            std::unique_lock<std::mutex> lck(data_mtx);
            while(running && data_queue.empty())
            {
                data_cond.wait(lck);
            }
            if (!running)
            {
                break;
            }
            data = data_queue.front();
            data_queue.pop();
        }
        if(!handle(data))
        {
            return;
        }
    }
}


void processor::add_data(const data_t &d)
{
    if (!running)
    {
        return;
    }
    std::lock_guard<std::mutex> lck(data_mtx);
    data_queue.push(d);
    data_cond.notify_all();
}

void processor::stop(bool force)
{
    std::lock_guard<std::mutex> lck(status_mtx);
    if (!running)
    {
        return;
    }

    while(!force)
    {
        {
            std::lock_guard<std::mutex> lck(data_mtx);
            if (data_queue.empty())
            {
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    running = false;
    data_cond.notify_all();
    for (auto &i : workers)
    {
        if (i.get()->joinable())
        {
            i.get()->join();
        }
    }
}


