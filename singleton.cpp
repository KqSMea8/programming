#include <iostream>
#include <mutex>


class SingleTon {
	public:
	      static SingleTon *getInstance();
	private:
	      SingleTon();
	      ~SingleTon();
	      static SingleTon *m_instance;
              static std::mutex m_mutex;
};

SingleTon * SingleTon::m_instance = NULL;
std::mutex SingleTon::m_mutex;

SingleTon::SingleTon() {
	std::cout << __FUNCTION__ << ", " << __LINE__ << std::endl;
}

SingleTon::~SingleTon() {
	std::cout << __FUNCTION__ << ", " << __LINE__ << std::endl;
}

SingleTon* SingleTon::getInstance() {
	std::cout << __FUNCTION__ << ", " << __LINE__ << std::endl;
	if (NULL == m_instance) {
		std::lock_guard<std::mutex> lck(m_mutex);
		if (NULL == m_instance) {
			m_instance = new SingleTon();
		}
	}
	return m_instance;
}

int main() {
	SingleTon *p = SingleTon::getInstance();
	SingleTon *q = SingleTon::getInstance();
	std::cout << p << ", " << q << std::endl;
	return 0;
}
