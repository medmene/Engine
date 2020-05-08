#pragma once
#include "LevelBase.h"



class Level1 : public LevelBase
{
public:
	Level1(shared_ptr<WindowManager> wm, SDL_Renderer * renderer, const Vector2 & winSize);

	static string GetName() { return "level_1"; }
	string GetWindowName() override { return GetName(); }
	
	void Run() override;
private:
};