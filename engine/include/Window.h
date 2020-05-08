#pragma once
#include "Core.h"
#include "Vector2.h"

class WindowManager;

class Window
{
public:
	Window(shared_ptr<WindowManager> wm, SDL_Renderer * r, const Vector2 & wSize);
	virtual ~Window() = default;

	virtual string GetWindowName() { return ""; }
	
	virtual void Run();
	virtual void Stop();
	virtual void Disappear() {}
	
	virtual void Render(){}
	virtual void Update(float dt){}
protected:
	shared_ptr<WindowManager>		m_wManager;
	SDL_Renderer				  * m_renderer = nullptr;
	Vector2							m_winSize;
	
private:
	int								m_framesBeforeStop;
	bool							m_stopped;
	bool							m_runned;
	int								m_layer;
	friend class WindowManager;
};