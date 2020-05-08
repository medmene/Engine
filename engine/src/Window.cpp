#include "include/Window.h"
#include "include/WindowManager.h"


Window::Window(shared_ptr<WindowManager> wm, SDL_Renderer * r, const Vector2 & wSize)
	: m_wManager(wm)
	, m_renderer(r)
	, m_winSize(wSize)
	, m_framesBeforeStop(0)
	, m_stopped(false)
	, m_layer(0)
{
}

void Window::Run()
{
	m_runned = true;
	m_stopped = false;
}

void Window::Stop()
{
	m_framesBeforeStop = 2;
	m_stopped = true;
	m_runned = false;
}
