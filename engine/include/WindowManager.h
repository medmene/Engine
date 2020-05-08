#pragma once
#include "base_defs.h"
#include "Vector2.h"

class Window;

class WindowManager
{
public:
	WindowManager();
	~WindowManager();

	void AddWindow(Window *w);
	
	void Render();
	void Update(float dt);
private:
	Vector2					m_layersRange;
	vector<Window*>			m_windows;
};