#pragma once
#include "BaseWindow.h"

class WindowManager;

class Window : public BaseWindow
{
public:
	Window(shared_ptr<WindowManager> wm);
	virtual ~Window() = default;

	virtual string GetWindowName() { return m_windowName; }
	
	virtual void Run();
	virtual void Stop();
	virtual void Disappear() {}
	virtual void LoadScene() {}
	
	virtual void Render(){}
	virtual void Update(float dt){}
protected:
	shared_ptr<WindowManager>		m_wManager;
	string							m_windowName;
	
private:
	int								m_framesBeforeStop;
	bool							m_stopped;
	bool							m_runned;
	int								m_layer;
	friend class WindowManager;
};