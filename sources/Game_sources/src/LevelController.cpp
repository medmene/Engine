#include "Game_sources/include/LevelController.h"



LevelController * LevelController::sm_instance = nullptr;

LevelController* LevelController::instance()
{
	if (!sm_instance)
	{
		sm_instance = new LevelController();
	}
	return sm_instance;
}


