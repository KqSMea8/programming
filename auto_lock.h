#include <pthread.h>

class AutoLock {
  private:
    pthread_mutex_t *mutex;
    AutoLock(const AutoLock &);
    AutoLock &operator=(const AutoLock &);

  public:
    AutoLock(pthread_mutex_t *mtx) {
      this->mutex = mtx;
      pthread_mutex_lock(mutex);
    }
    ~AutoLock() {
      pthread_mutex_unlock(mutex);
    }
};

