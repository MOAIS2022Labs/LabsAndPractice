#pragma once
#include <map>
#include <list>

template <class TKey, class TValue>
class Dictionary
{
private:
	
	std::map<TKey, TValue> _map;

public:

	Dictionary<TKey, TValue>() {}
	Dictionary<TKey, TValue>(std::map<TKey, TValue> mp)
	{
		_map = mp;
	}

	std::map<TKey, TValue> get_map()
	{
		return _map;
	}

	std::list<TKey> keys()
	{
		std::list<TKey> result;
		for (auto& pr : _map)
			result.push_back(pr.first);
		return result;		
	}

	std::list<TValue> values()
	{
		std::list<TValue> result;
		for (auto& pr : _map)
			result.push_back(pr.second);
		return result;
	}
};