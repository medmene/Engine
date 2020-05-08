#include "include/WindowManager.h"
#include "include/PassabilityMap.h"
#include "include/Window.h"



WindowManager::WindowManager(SDL_Renderer *r, const Vector2 & wSize)
	: m_renderer(r)
	, m_windowSize(wSize)
	, m_breakUpdate(false)
	, m_breakRender(true)
{
}

WindowManager::~WindowManager()
{
	for (auto && wnd : m_windows)
	{
		wnd->Disappear();
	}
	m_windows.clear();
}

void WindowManager::SetWindowLevel(const string& name, int layer)
{
	for (auto && wnd : m_windows)
	{
		if (wnd->GetWindowName() == name)
		{
			wnd->m_layer = layer;
			break;
		}
	}
	SortWindows();
}

void WindowManager::Render()
{
	for (auto && wnd : m_windows)
	{
		if (m_breakRender) { break; }
		
		if (wnd->m_runned)
		{
			wnd->Render();
		}
	}
	
	if (m_breakRender)
	{
		for (auto && wnd : m_windows)
		{
			if (wnd->m_runned)
			{
				wnd->Render();
			}
		}
		m_breakRender = false;
	}
}

void WindowManager::Update(float dt)
{
	for (auto it = m_windows.begin(); it != m_windows.end();)
	{
		if (m_breakUpdate) { break; }
		
		if ((*it)->m_stopped)
		{
			(*it)->m_framesBeforeStop--;
			if ((*it)->m_framesBeforeStop == 0)
			{
				(*it)->Disappear();
				it = m_windows.erase(it);
				m_breakUpdate = true;
			}
			else
			{
				++it;
			}
		}
		else
		{
			if ((*it)->m_runned)
			{
				(*it)->Update(dt);
			}
			if (m_breakUpdate) { break; }
			++it;
		}
	}

	if (m_breakUpdate)
	{
		for (auto && wnd : m_windows)
		{
			if (wnd->m_runned)
			{
				wnd->Update(dt);
			}
		}
		m_breakUpdate = false;
	}
}

bool WindowManager::SortComparer(const shared_ptr<Window> &lhs, const shared_ptr<Window> &rhs)
{
	return lhs->m_layer < rhs->m_layer;
}

void WindowManager::SortWindows()
{
	std::sort(m_windows.begin(), m_windows.end(), SortComparer);
}

int WindowManager::GetUniqLayer()
{
	int i = m_windows.size();
	bool finded;
	
	while (true)
	{
		finded = true;
		for (auto && wnd : m_windows)
		{
			if (wnd->m_layer == i)
			{
				finded = false;
				break;
			}
		}

		if (finded == true)
		{
			return i;
		}
		i++;
	}
}
