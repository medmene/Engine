#pragma once
#include "include/base_defs.h"


class GameObject;

class ScriptItem
{
public:
	ScriptItem() = default;

	string GetName() const { return m_itemName; }
	GameObject * GetObject() { return m_object; }

	void Run();
 
private:
	GameObject			  * m_object = nullptr;
	string					m_itemName;
};

class Script
{
public:
	Script() = default;
private:
	
};

class ScriptManager
{
	ScriptManager() = default;
public:
	static ScriptManager * instance();

	void LoadScript(const string & res);
private:

	static ScriptManager * sm_instance;
};