#pragma once
#include "base_defs.h"



template <class Key>
class ActionMap
{
	ActionMap() = default;
public:
	void Call(const Key & key);

	void AddAction(const Key & key, const std::function<void()>& action);
	
	void Clear(const Key & key);
	void Clear();
private:
	
	multimap<Key, std::function<void()>> m_actions;
};

template <class Key>
void ActionMap<Key>::Call(const Key& key)
{
	if (!m_actions.empty())
	{
		auto range = m_actions.equal_range(key);
		for (auto it = range.first; it != range.second; ++it)
		{
			it->second();
		}
	}
}

template <class Key>
void ActionMap<Key>::AddAction(const Key& key, const std::function<void()>& action)
{
	if (action)
	{
		m_actions.emplace(key, action);
	}
}

template <class Key>
void ActionMap<Key>::Clear(const Key& key)
{
	m_actions.erase(key);
}

template <class Key>
void ActionMap<Key>::Clear()
{
	m_actions.clear();
}
