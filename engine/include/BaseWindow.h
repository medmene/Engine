#pragma once
#include "Core.h"
#include "Vector2.h"

class BaseWindow
{
public:
	static void Setup(SDL_Renderer *r, const Vector2 & wSize);
protected:
	static SDL_Renderer			  * m_renderer;
	static Vector2					m_winSize;
	BaseWindow() = default;
};