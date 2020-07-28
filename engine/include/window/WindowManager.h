#pragma once
#include "include/Core.h"
#include "include/types/Vector2.h"

class Window;

class WindowManager : public std::enable_shared_from_this<WindowManager>
{
public:
	WindowManager(SDL_Renderer *r, const Vector2 & wSize);
	~WindowManager();

	template <typename TWindowType>
	shared_ptr<TWindowType> CreateAndRunWindow();
	template <typename TWindowType>
	shared_ptr<TWindowType> CreateWindow();

	void SetWindowLevel(const string & name, int layer);
	
	void Render();
	void Update(float dt);
private:
	SDL_Renderer					  * m_renderer = nullptr;
	Vector2								m_windowSize;
	vector<shared_ptr<Window>>			m_windows;
	bool								m_breakUpdate;
	bool								m_breakRender;

	static bool SortComparer(const shared_ptr<Window> &lhs, const shared_ptr<Window> &rhs);
	void SortWindows();
	int GetUniqLayer();
};

template <typename TWindowType>
shared_ptr<TWindowType> WindowManager::CreateAndRunWindow()
{
	auto window = CreateWindow<TWindowType>();
	window->Run();
	return window;
}

template <typename TWindowType>
shared_ptr<TWindowType> WindowManager::CreateWindow()
{
	shared_ptr<TWindowType> window = make_shared<TWindowType>(shared_from_this());
	window->m_layer = GetUniqLayer();
	window->LoadScene();
	m_windows.emplace_back(window);
	
	m_breakUpdate = true;
	m_breakRender = true;
	SortWindows();
	
	return window;
}
