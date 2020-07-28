#include "include/window/Window.h"
#include "include/window/WindowManager.h"


Window::Window(shared_ptr<WindowManager> wm)
	: BaseWindow()
	, m_wManager(wm)
	, m_framesBeforeStop(0)
	, m_stopped(false)
	, m_runned(false)
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
