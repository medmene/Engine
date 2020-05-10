#pragma once
#include "LevelBase.h"


class Menu : public LevelBase
{
public:
	explicit Menu(shared_ptr<WindowManager> wm);
	
	void Run() override;
private:
};