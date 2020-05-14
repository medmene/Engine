#pragma once
#include "LevelBase.h"

class Player;

class Level1 : public LevelBase
{
public:
	Level1(shared_ptr<WindowManager> wm);
	
	void Run() override;
private:
	Player * pl = nullptr;
};