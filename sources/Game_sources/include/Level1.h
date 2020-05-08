#pragma once
#include "LevelBase.h"



struct Level1 : public LevelBase
{
	Level1(WindowManager * wm);

	void Init(SDL_Renderer * renderer, const Vector2 & winSize) override;
};