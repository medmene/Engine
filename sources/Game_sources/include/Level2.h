#pragma once
#include "LevelBase.h"




struct Level2 : public LevelBase
{
	Level2(WindowManager * wm);

	void Init(SDL_Renderer * renderer, const Vector2 & winSize) override;
};