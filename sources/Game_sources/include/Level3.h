#pragma once
#include "LevelBase.h"



struct Level3 : public LevelBase
{
	Level3() = default;

	void Init(SDL_Renderer * renderer, const Vector2 & winSize) override;
};