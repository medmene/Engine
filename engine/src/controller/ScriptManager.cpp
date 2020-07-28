#include "include/controller/ScriptManager.h"





ScriptManager * ScriptManager::sm_instance = nullptr;

ScriptManager* ScriptManager::instance()
{
	if (!sm_instance)
	{
		sm_instance = new ScriptManager();
	}
	return sm_instance;
}

void ScriptManager::LoadScript(const string& res)
{
}
