#include "Game_sources/include/LevelBase.h"
#include "include/GameObject.h"
#include "include/NPC.h"



LevelBase::LevelBase(shared_ptr<WindowManager> wm)
	: Window(wm)
{
	m_windowName = "level_base";
}

void LevelBase::Run()
{
	Window::Run();
}

void LevelBase::Disappear()
{
	for (auto && obj : m_objects)
	{
		delete obj;
	}
	m_objects.clear();
}

void LevelBase::Update(float dt)
{
	for (auto && obj : m_objects)
	{
		obj->Update(dt);
	}
}

void LevelBase::Render()
{
	for (auto && obj : m_objects)
	{
		obj->Render();
	}
}
