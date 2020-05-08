#include "include/WindowManager.h"
#include "include/PassabilityMap.h"
#include "include/Window.h"



WindowManager::WindowManager()
{
	m_layersRange = Vector2(-1, PassabilityMap::instance()->GetMapSize().y + 1);
}

WindowManager::~WindowManager()
{
	for (auto && wnd : m_windows)
	{
		delete wnd;
	}
}

void WindowManager::AddWindow(Window* w)
{
	m_windows.emplace_back(w);
}

void WindowManager::Render()
{
	for (auto && wnd : m_windows)
	{
		wnd->Render();
	}
}

void WindowManager::Update(float dt)
{
	for (auto && wnd : m_windows)
	{
		wnd->Update(dt);
	}
}
