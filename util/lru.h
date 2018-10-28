#ifndef __LRU__
#define __LRU__

#include <list>
#include <unordered_map>
#include <cassert>

template<class K, class V>
class LRU
{
public:
	LRU(size_t max_size)
	{
		this->max_size = max_size;
		assert(max_size > 0);
	}
	template<typename KEY, typename VALUE>
	void push(KEY &&key, VALUE &&value)
	{
		if (cached(key))
		{
			return;
		}
		cache_list.emplace_front(key, std::forward<VALUE>(value));
		cache_map.emplace(std::forward<KEY>(key), cache_list.begin());
		if (cache_map.size() > max_size)
		{
			cache_map.erase(cache_list.back().first);
			cache_list.pop_back();
		}
	}
	std::pair<K, V> &get(const K &key)
	{
		auto it = cache_map.find(key);
		if (it == cache_map.end())
		{
			throw std::out_of_range("LRU bad access.");
		}
		if (it->second != cache_list.begin())
		{
			cache_list.splice(cache_list.begin(), cache_list, it->second);
		}
		return *(it->second);
	}
	bool cached(const K &key) const
	{
		return cache_map.find(key) != cache_map.end();
	}
	bool full() const
	{
		return max_size == cache_map.size();
	}
	void clear()
	{
		cache_map.clear();
		cache_list.clear();
	}
	
private:
	std::list <std::pair<K, V>> cache_list;
	std::unordered_map<K, typename decltype(cache_list)::iterator> cache_map;
	size_t max_size;
};

#endif
