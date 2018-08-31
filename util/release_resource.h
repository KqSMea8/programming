#ifndef __RELEASE_RESOURCE__
#define __RELEASE_RESOURCE__
#include <functional>

template<class Resource, class Callable>
struct release_resource
{
	release_resource(Resource resource, Callable target) :
		m_resource(resource),
		m_release(target)
	{
	}
	~release_resource()
	{
		m_release(m_resource);
	}
	void reset(Resource resource)
	{
		m_release(m_resource);
		m_resource = resource;
	}
	release_resource(const release_resource &) = delete;
	release_resource &operator=(const release_resource &) = delete;
private:
	Resource m_resource;
	std::function<Callable> m_release;
};

#endif