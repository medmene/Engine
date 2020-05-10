#include "include/BaseObject.h"


SDL_Renderer * BaseObject::m_renderer = nullptr;

void BaseObject::SetupRendered(SDL_Renderer* r)
{
	if (m_renderer == nullptr)
	{
		m_renderer = r;
	}
}
