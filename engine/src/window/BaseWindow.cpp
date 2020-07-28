#include "include/window/BaseWindow.h"



SDL_Renderer * BaseWindow::m_renderer = nullptr;
Vector2 BaseWindow::m_winSize = Vector2::zero;

void BaseWindow::Setup(SDL_Renderer* r, const Vector2& wSize)
{
	if (m_renderer == nullptr)
	{
		m_renderer = r;
	}
	
	m_winSize = wSize;
}
