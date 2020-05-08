#pragma once

class WindowManager;

class Window
{
public:
	Window(WindowManager * wm);
	virtual ~Window() = default;
	virtual void Render(){}
	virtual void Update(float dt){}
protected:
	WindowManager		  * m_wManager = nullptr;
private:
	int						m_layer;
	friend class WindowManager;
};