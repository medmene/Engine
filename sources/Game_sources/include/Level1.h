#pragma once
#include "LevelBase.h"

class GameObject;
class NPC;

struct Level1 : public LevelBase
{
	Level1() = default;

	void Init(SDL_Renderer * renderer, const Vector2 & winSize) override;
};