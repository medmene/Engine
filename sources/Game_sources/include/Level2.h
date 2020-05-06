#pragma once
#include "LevelBase.h"

class GameObject;
class NPC;

struct Level2 : public LevelBase
{
	Level2() = default;

	void Init(SDL_Renderer * renderer, const Vector2 & winSize) override;
};