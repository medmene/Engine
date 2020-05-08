#pragma once
#include "LevelBase.h"


class Menu : public LevelBase
{
public:
	explicit Menu(shared_ptr<WindowManager> wm, SDL_Renderer *r, const Vector2 & winSize);
	
	static string GetName() { return "game_menu"; }
	string GetWindowName() override { return GetName(); }
	
	void Run() override;
private:
};