#pragma once
#include "include/tools/FunctionParam.h"



#if false
class ActionCallbacks
{
	std::function<void()>	func;
public:
	template<typename TObject, typename TMethod, typename ...TArgs>
	ActionCallbacks(weak_ptr<TObject> owner, TMethod method, TArgs ...args)
	{ 
		auto bind = std::bind(method, /*owner.lock().get(),*/ args...);
		func = [owner, bind]()
		{
			if (!owner.expired())
			{
				bind();
			}
		};
	}

	void Handle()
	{
		std::shared_ptr<T> ptr = object.lock();
		if (ptr)
		{
			(ptr.get()->*callback)(arg...);
		}
	}
};


template <typename T, typename... Args>
class ActionCallback
{
	weak_ptr<T> object;
	void (T::*callback)(Args...);
public:
	ActionCallback(weak_ptr<T> who, void (T::*func)(Args...))
		: object(who), callback(func)
	{ }

	void Handle(Args... arg)
	{
		std::shared_ptr<T> ptr = object.lock();
		if (ptr)
		{
			(ptr.get()->*callback)(arg...);
		}
	}
};

#endif

//class CallbackWrapper 
//{
//public:
//	template <typename T, typename... Args>
//	CallbackWrapper(weak_ptr<T> who, void (T::*func)(Args...))
//	{
//		auto action = ActionCallback<T, Args...>(who, func);
//		func = [action]()
//	}
//
//};


//class Callback 
//{
//public:
//	Callback();
//	Callback(std::function<void(FunctionParamWrapper)> func);
//
//	template<class Class>
//	Callback(const std::shared_ptr<Class> & shared, const std::function<void(const FunctionParamWrapper &)> & func);
//
//	template<class ClassPointer, class Class>
//	Callback(const std::shared_ptr<ClassPointer> & shared, void (Class::*method)(const FunctionParamWrapper &));
//
//	template<class ClassPointer, class Class>
//	Callback(const std::shared_ptr<ClassPointer> & shared, void (Class::*method)());
//
//	//template<typename TObject, typename TMethod, typename... TArgs>
//	//Callback(weak_ptr<TObject> owner, TMethod method, TArgs ...args);
//
//	//template<typename TObject, typename TMethod, typename... TArgs>
//	//Callback(shared_ptr<TObject> owner, TMethod method, TArgs ...args);
//
//	void operator() (const FunctionParamWrapper & param) const;
//	operator bool() const;
//
//protected:
//	bool												m_useObject;
//	weak_ptr<void>										m_object;
//	std::function<void(FunctionParamWrapper)>			m_function;
//	std::function<void()>			m_functions;
//};
//
//template<class Class>
//inline Callback::Callback(const std::shared_ptr<Class>& shared, const std::function<void(const FunctionParamWrapper&)>& func)
//	: m_useObject(true)
//	, m_function(func)
//	, m_object(shared)
//{
//}
//
//template<class ClassPointer, class Class>
//inline Callback::Callback(const std::shared_ptr<ClassPointer>& shared, void(Class::* method)(const FunctionParamWrapper &))
//{
//	weak_ptr<Class> weakThis = dynamic_pointer_cast<Class>(shared);
//	m_object = dynamic_pointer_cast<void>(sharedThis);
//
//	m_function = std::function<void(const FunctionParamWrapper &)>([weakThis, method](const FunctionParamWrapper & param)
//	{
//		std::shared_ptr<Class> ptr = weakThis.lock();
//		if (ptr)
//		{
//			(ptr.get()->*method)(param);
//		}
//	});
//}
//
//template<class ClassPointer, class Class>
//inline Callback::Callback(const std::shared_ptr<ClassPointer>& shared, void(Class::* method)())
//{
//	weak_ptr<Class> weakThis = dynamic_pointer_cast<Class>(shared);
//	m_object = dynamic_pointer_cast<void>(sharedThis);
//
//	m_function = std::function<void(const FunctionParamWrapper &)>([weakThis, method](const FunctionParamWrapper & param)
//	{
//		std::shared_ptr<Class> ptr = weakThis.lock();
//		if (ptr)
//		{
//			(ptr.get()->*method)();
//		}
//	});
//}

//template<typename TObject, typename TMethod, typename ...TArgs>
//inline Callback::Callback(weak_ptr<TObject> owner, TMethod method, TArgs ...args)
//{
//	auto bind = std::bind(method, owner.lock().get(), args...);
//	m_function = [owner, bind]()
//	{
//		if (!owner.expired())
//		{
//			bind();
//		}
//	};
//}
//
//template<typename TObject, typename TMethod, typename ...TArgs>
//inline Callback::Callback(shared_ptr<TObject> owner, TMethod method, TArgs ...args)
//{
//	weak_ptr<TObject> weakPtr = owner;
//	Callback(weakPtr, method, args...);
//}




//template <class Key>
//class ActionMap
//{
//	ActionMap() = default;
//public:
//	void Call(const Key & key, const ActionCallback & param = {});
//
//	void AddAction(const Key & key, const ActionCallback& callback);
//	
//	void Clear(const Key & key);
//	void Clear();
//private:
//	
//	multimap<Key, ActionCallback> m_actions;
//};
//
//template <class Key>
//void ActionMap<Key>::Call(const Key& key, const ActionCallback & param)
//{
//	if (!m_actions.empty())
//	{
//		auto range = m_actions.equal_range(key);
//		for (auto it = range.first; it != range.second; ++it)
//		{
//			it->second(param);
//		}
//	}
//}
//
//template <class Key>
//void ActionMap<Key>::AddAction(const Key& key, const ActionCallback& callback)
//{
//	if (callback)
//	{
//		m_actions.emplace(key, action);
//	}
//}
//
//template <class Key>
//void ActionMap<Key>::Clear(const Key& key)
//{
//	m_actions.erase(key);
//}
//
//template <class Key>
//void ActionMap<Key>::Clear()
//{
//	m_actions.clear();
//}
