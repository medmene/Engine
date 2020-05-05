#pragma once
#include "LevelBase.h"


struct Menu : public LevelBase
{
	Menu() = default;

	void Init(SDL_Renderer * renderer, const Vector2 & winSize) override;
};