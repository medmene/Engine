#pragma once
#include "include/controller/other/FunctionParam.h"

class Callback 
{
public:
	Callback();
	Callback(std::function<void(FunctionParamWrapper)> func);

	template<class Class>
	Callback(const std::shared_ptr<Class> & shared, const std::function<void(const FunctionParamWrapper &)> & func);

	template<class ClassPointer, class Class>
	Callback(const std::shared_ptr<ClassPointer> & shared, void (Class::*method)(const FunctionParamWrapper &));

	template<class ClassPointer, class Class>
	Callback(const std::shared_ptr<ClassPointer> & shared, void (Class::*method)());

	void operator() (const FunctionParamWrapper & param) const;
	operator bool() const;

protected:
	bool												m_useObject;
	weak_ptr<void>										m_object;
	std::function<void(FunctionParamWrapper)>	m_function;
};

template<class Class>
inline Callback::Callback(const std::shared_ptr<Class>& shared, const std::function<void(const FunctionParamWrapper&)>& func)
	: m_useObject(true)
	, m_function(func)
	, m_object(shared)
{
}

template<class ClassPointer, class Class>
inline Callback::Callback(const std::shared_ptr<ClassPointer>& shared, void(Class::* method)(const FunctionParamWrapper &))
{
	weak_ptr<Class> weakThis = dynamic_pointer_cast<Class>(sharedThis);
	m_object = dynamic_pointer_cast<void>(sharedThis);

	m_function = std::function<void(const FunctionParamWrapper &)>([weakThis, method](const FunctionParamWrapper & param)
	{
		std::shared_ptr<Class> ptr = weakThis.lock();
		if (ptr)
		{
			(ptr.get()->*method)(param);
		}
	});
}

template<class ClassPointer, class Class>
inline Callback::Callback(const std::shared_ptr<ClassPointer>& shared, void(Class::* method)())
{
	weak_ptr<Class> weakThis = dynamic_pointer_cast<Class>(sharedThis);
	m_object = dynamic_pointer_cast<void>(sharedThis);

	m_function = std::function<void(const FunctionParamWrapper &)>([weakThis, method](const FunctionParamWrapper & param)
	{
		std::shared_ptr<Class> ptr = weakThis.lock();
		if (ptr)
		{
			(ptr.get()->*method)();
		}
	});
}




template <class Key>
class ActionMap
{
	ActionMap() = default;
public:
	void Call(const Key & key, const FunctionParamWrapper & param = {});

	void AddAction(const Key & key, const Callback& callback);
	
	void Clear(const Key & key);
	void Clear();
private:
	
	multimap<Key, Callback> m_actions;
};

template <class Key>
void ActionMap<Key>::Call(const Key& key, const FunctionParamWrapper & param)
{
	if (!m_actions.empty())
	{
		auto range = m_actions.equal_range(key);
		for (auto it = range.first; it != range.second; ++it)
		{
			it->second(param);
		}
	}
}

template <class Key>
void ActionMap<Key>::AddAction(const Key& key, const Callback& callback)
{
	if (callback)
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
