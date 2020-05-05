#pragma once
#include "LevelBase.h"
#include "include/Core.h"

class LevelController
{
public:

	static LevelController * instance();
private:
	LevelController() = default;
	vector<LevelBase>				m_levels;
	
	static LevelController		  * sm_instance;
};