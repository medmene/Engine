#pragma once
#include "GameSceneBase.h"

class Player;

class Level1 : public GameSceneBase
{
public:
	Level1(shared_ptr<WindowManager> wm);
	
	void LoadScene() override;

	void Run() override;
private:
	Player * pl = nullptr;
};