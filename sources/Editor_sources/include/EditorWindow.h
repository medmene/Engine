#pragma once
#include "include/Core.h"
#include "include/sVector2.h"
#include "include/sGameObject.h"

class sGameObject;

class GameWindow
{
public:
	GameWindow();
	GameWindow(bool fullScreeen);
	GameWindow(const sVector2 &size);
	~GameWindow();
	static GameWindow * instance() { return sm_instance; }

	SDL_Window * GetRawWindow();

	void Initialize();
	int ProcessEvents();

private:
	SDL_Window				  * m_window;
	SDL_DisplayMode				m_displayMode;
	SDL_Renderer			  * m_renderer;

	sGameObject				  * m_gameObject;
	sGameObject				  * m_root;

	sVector2					m_windowSize;

	void Update();
	void DrawTexture(sGameObject * obj);
	static GameWindow * sm_instance;
};