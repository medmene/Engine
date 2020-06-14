#pragma once
#include "GameSceneBase.h"


class Menu : public GameSceneBase
{
public:
	explicit Menu(shared_ptr<WindowManager> wm);
	
	void Run() override;
private:
};