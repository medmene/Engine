#pragma once
#include "include/Core.h"
#include "include/Vector2.h"
#include "include/Fps.h"


class Label;
class Button;
class GameObject;
class Player;
class NPC;
struct Level1;
class GameInterface;
struct Level2;
struct Menu;

class GameWindow
{
public:
	enum State
	{
		MENU = 0,
		LEVEL1,
		LEVEL2,
		LEVEL3,
		LEVEL4
	};


	GameWindow();
	~GameWindow();
	static GameWindow * instance() { return sm_instance; }

	void Initialize();
	void Update();
	
	Player * GetPlayer() { return m_player; }

private:
	SDL_Window					  * m_window = nullptr;
	SDL_DisplayMode					m_displayMode;
	SDL_Renderer				  * m_renderer = nullptr;
	Vector2							m_windowSize;
	_FPS							FPS;

	GameInterface				  * m_interface;
	
	State							m_state = State::MENU;

	Menu						  * m_menu = nullptr;
	Level1						  * m_level1 = nullptr;
	Level2						  * m_level2 = nullptr;
	Player						  * m_player = nullptr;
	NPC							  * m_npc = nullptr;

	static GameWindow			  * sm_instance;
};