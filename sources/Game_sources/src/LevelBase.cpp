#include "Game_sources/include/LevelBase.h"
#include "include/GameObject.h"
#include "include/NPC.h"



LevelBase::LevelBase(shared_ptr<WindowManager> wm)
	: Window(wm)
	, m_useSort(true)
{
	m_windowName = "level_base";
}

void LevelBase::Run()
{
	Window::Run();
}

void LevelBase::Disappear()
{
	for (auto && ground : m_groundObjects)
	{
		ground->Render();
	}
	m_groundObjects.clear();
	
	for (auto && obj : m_objects)
	{
		delete obj;
	}
	m_objects.clear();
}

void LevelBase::Update(float dt)
{
	for (auto && ground : m_groundObjects)
	{
		ground->Update(dt);
	}
	
	for (auto && obj : m_objects)
	{
		obj->Update(dt);
	}
}

void LevelBase::Render()
{
	for (auto && ground : m_groundObjects)
	{
		ground->Render();
	}
	
	if (m_useSort)
	{
		std::sort(m_objects.begin(), m_objects.end(), SortComparer);
		for (auto && obj : m_objects)
		{
			obj->Render();
		}
	}
}

bool LevelBase::SortComparer(const GameObject* lhs, const GameObject* rhs)
{
	return lhs->GetPivotPos().y < rhs->GetPivotPos().y;
}
