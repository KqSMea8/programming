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
		this->cur_size = 0;
	}
	template<typename KEY, typename VALUE>
	void push(KEY &&key, VALUE &&value)
	{
		if (cached(key))
		{
			return;
		}
		cache_list.emplace_front(std::forward<KEY>(key), std::forward<VALUE>(value));
		cache_map.emplace(std::forward<KEY>(key), cache_list.begin());
		cur_size++;
		if (cur_size > max_size)
		{
			cache_map.erase(cache_list.back().first);
			cache_list.pop_back();
			cur_size--;
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
	bool cached(const K &key) const noexcept
	{
		return cache_map.find(key) != cache_map.end();
	}
	bool full() const noexcept
	{
		return max_size == cur_size;
	}
	
private:
	std::list <std::pair<K, V>> cache_list;
	typedef typename std::list <std::pair<K, V>>::iterator cache_list_iterator;
	std::unordered_map<K, cache_list_iterator> cache_map;
	size_t max_size;
	size_t cur_size;
};

#endif
