#include "GlobalWindowManager.h"


GlobalWindowManager * GlobalWindowManager::sm_instance = new GlobalWindowManager();

GlobalWindowManager::~GlobalWindowManager()
{
	FreeWindows();
}

void GlobalWindowManager::RegisterWindow(GlobalWindow* win)
{
	m_windows.push_back(win);
}

void GlobalWindowManager::RegisterWindowAndInitialize(GlobalWindow* win)
{
	win->Initialize();
	m_windows.push_back(win);
}

void GlobalWindowManager::DestroyWindow(int index)
{
	auto it = m_windows.begin();
	for (int iter = 0; iter < index; iter += 1)
	{
		++it;
	}
	if (it != m_windows.end())
	{
		GlobalWindow * win = *it;
		m_windows.erase(it);
		delete win;
	}
}

void GlobalWindowManager::DisposeWindows()
{
	while (m_toDestroy.size() > 0)
	{
		auto toDelete = m_toDestroy.begin();
		while (m_windows.size() > 0)
		{
			auto it = m_windows.begin();
			if ((*it) == (*toDelete))
			{
				GlobalWindow * win = (*it);
				m_windows.erase(it);
				m_toDestroy.erase(toDelete);
				delete win;
			}
		}
	}
}

bool GlobalWindowManager::isUniqInDestroy(GlobalWindow* window)
{
	for (auto && item : m_toDestroy)
	{
		if (item == window)
		{
			return false;
		}
	}
	return true;
}

void GlobalWindowManager::FreeWindows()
{
	while (m_windows.size() > 0)
	{
		auto it = m_windows.begin();
		GlobalWindow * win = *it;
		m_windows.erase(it);
		delete win;
	}
	while (m_toDestroy.size() > 0)
	{
		auto it = m_toDestroy.begin();
		GlobalWindow * win = *it;
		m_toDestroy.erase(it);
		delete win;
	}
}

int GlobalWindowManager::GetWindowCount() const
{
	return m_windows.size();
}

void GlobalWindowManager::ProcessWindows()
{
	while (m_windows.size() > 0)
	{
		SDL_Event e;

		while (SDL_PollEvent(&e) > 0)
		{
			for (auto it = m_windows.begin(); it != m_windows.end(); ++it)
			{
				if ((*it)->ProcessEvents(e) == -1)
				{
					if (isUniqInDestroy(*it))
					{
						m_toDestroy.push_back(*it);
					}
				}
			}
		}
		if (m_toDestroy.size() > 0)
		{
			DisposeWindows();
		}
	}
}
