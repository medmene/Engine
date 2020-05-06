#pragma once
#include "LevelBase.h"



struct Level1 : public LevelBase
{
	Level1() = default;

	void Init(SDL_Renderer * renderer, const Vector2 & winSize) override;
};