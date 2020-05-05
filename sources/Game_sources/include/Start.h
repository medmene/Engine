#pragma once
#include "LevelBase.h"



struct Start : public LevelBase
{
	Start() = default;

	void Init(SDL_Renderer * renderer, const Vector2 & winSize) override;
};