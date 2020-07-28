#include "include/tools/ActionMap.h"




Callback::Callback()
	: m_useObject(false)
	, m_function(nullptr)
{
}

Callback::Callback(std::function<void(FunctionParamWrapper)> func)
	: m_useObject(false)
	, m_function(func)
{
}

void Callback::operator()(const FunctionParamWrapper & param) const
{
	auto shrd = m_object.lock();

	if (m_function && (shrd || !m_useObject)) 
	{
		m_function(param);
	}
}

Callback::operator bool() const
{ 
	return (bool)m_function; 
}
