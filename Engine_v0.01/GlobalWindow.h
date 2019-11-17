#pragma once
#include "Core.h"
#include "sVector2.h"

class sGameObject;

class GlobalWindow 
{
public:
	GlobalWindow();
	GlobalWindow(bool fullScreeen);
	GlobalWindow(const sVector2 &size);
	~GlobalWindow();

	SDL_Window* GetRawWindow();

	void Initialize();
	void DefaultBackground();
	int ProcessEvents(const SDL_Event &event);
private:
	SDL_Window				  * m_window;
	SDL_Renderer			  * m_renderer;
	SDL_DisplayMode				m_displayMode;
	
	sGameObject				  * m_gameObject;
	sGameObject				  * m_root;
	
	sVector2					m_windowSize;	
};
