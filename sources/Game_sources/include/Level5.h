#pragma once
#include "LevelBase.h"



struct Level5 : public LevelBase
{
	Level5(WindowManager * wm);

	void Init(SDL_Renderer * renderer, const Vector2 & winSize) override;
};