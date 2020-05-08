#include "include/Window.h"
#include "include/WindowManager.h"


Window::Window(WindowManager * wm)
	: m_wManager(wm)
	, m_layer(0)
{
}
