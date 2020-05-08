#pragma once
#include "LevelBase.h"



struct Level4 : public LevelBase
{
	Level4(WindowManager * wm);

	void Init(SDL_Renderer * renderer, const Vector2 & winSize) override;
};
