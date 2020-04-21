#pragma once
#include "include/Core.h"
#include "include/Vector2.h"
#include "include/Fps.h"


class Label;
class Button;
class GameObject;
class Player;
struct Level1;

class GameWindow
{
public:
	GameWindow();
	~GameWindow();
	static GameWindow * instance() { return sm_instance; }

	void Initialize();
	void Update();
private:
	SDL_Window					  * m_window;
	SDL_DisplayMode					m_displayMode;
	SDL_Renderer				  * m_renderer;
	Vector2							m_windowSize;
	_FPS							FPS;

	Level1						  * m_level1;
	Player						  * m_player;

	static GameWindow			  * sm_instance;
};