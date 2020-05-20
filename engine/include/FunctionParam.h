#pragma once
#include "base_defs.h"

class FunctionParamBase
{
public:
	FunctionParamBase() {}
	virtual ~FunctionParamBase() {}

	virtual FunctionParamBase * Clone() = 0;
};

template <class T>
class FunctionParam : public FunctionParamBase
{
public:
	FunctionParam(const T & param) : m_param(param) {}
	FunctionParamBase * Clone() override { return new FunctionParam<T>(m_param); }

	T m_param;
};

class FunctionParamWrapper
{
public:
	FunctionParamWrapper() = default;

	template <typename type>
	FunctionParamWrapper(const type & param) : m_param(new FunctionParam<type>(param)) {}

	FunctionParamWrapper(const FunctionParamWrapper & other)
	{
		m_param.reset(other.m_param ? other.m_param->Clone() : nullptr);
	}

	FunctionParamWrapper & operator=(const FunctionParamWrapper & other)
	{
		m_param.reset(other.m_param ? other.m_param->Clone() : nullptr);
		return *this;
	}

	template <typename type>
	FunctionParamWrapper & operator=(const type & param)
	{
		m_param.reset(new FunctionParam<type>(param));
		return *this;
	}

	template <typename type>
	type & Value()
	{
		if (!m_param) { *this = type(); }

		return static_pointer_cast<FunctionParam<type>>(m_param)->m_param;
	}
private:
	shared_ptr<FunctionParamBase> m_param;
};