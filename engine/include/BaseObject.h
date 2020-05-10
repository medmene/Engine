#pragma once
#include "Core.h"


class BaseObject
{
public:
	static void SetupRendered(SDL_Renderer *r);
protected:
	static SDL_Renderer			  * m_renderer;
	BaseObject() = default;
};