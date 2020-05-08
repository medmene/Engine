#pragma once
#include "include/Core.h"
#include "include/Vector2.h"
#include "include/Fps.h"


class GameObject;
class Player;
class GameInterface;

class GameWindow
{
public:
	GameWindow();
	~GameWindow();
	static GameWindow * instance() { return sm_instance; }

	void Initialize();
	void Processing(bool manually = false);
	
	Player * GetPlayer() { return m_player; }

private:
	void Update();
	void Render();
	
	SDL_Window					  * m_window = nullptr;
	SDL_DisplayMode					m_displayMode;
	SDL_Renderer				  * m_renderer = nullptr;
	Vector2							m_windowSize;
	_FPS							FPS;
	GameInterface				  * m_interface;
	Player						  * m_player = nullptr;

	static GameWindow			  * sm_instance;

	friend class GameModeChangeController;
};