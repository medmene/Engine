#pragma once
#include "include/Core.h"
#include "include/types/Vector2.h"
#include "include/tools/Fps.h"
#include "include/window/WindowManager.h"


class GameObject;
class Player;
class GameInterface;

class GameWindow
{
	GameWindow();
public:
	~GameWindow();
	static GameWindow * instance();

	void Initialize();
	void Processing();
	
	Player * GetPlayer() { return m_player; }
	shared_ptr<WindowManager> GetWindowManager() { return m_windowManager; }

private:
	void Update();
	void Render();
	void LoadPlayer();
	
	SDL_Window					  * m_window = nullptr;
	SDL_DisplayMode					m_displayMode;
	SDL_Renderer				  * m_renderer = nullptr;
	Vector2							m_windowSize;
	_FPS							FPS;
	
	shared_ptr<WindowManager>		m_windowManager;
	Player						  * m_player = nullptr;

	static GameWindow			  * sm_instance;

	friend class GameModeChangeController;
};