#include "Game_sources/include/LevelBase.h"
#include "include/GameObject.h"
#include "include/NPC.h"

LevelBase::~LevelBase()
{
	for (auto && obj : m_objects)
	{
		delete obj;
	}
	m_objects.clear();

	for (auto&& npc : m_npcs)
	{
		delete npc;
	}
	m_npcs.clear();
}

void LevelBase::Update(float dt)
{
	for (auto && obj : m_objects)
	{
		obj->Update(dt);
	}

	for (auto&& npc : m_npcs)
	{
		npc->Update(dt);
	}
}

void LevelBase::Render()
{
	for (auto && obj : m_objects)
	{
		obj->Render();
	}

	for (auto&& npc : m_npcs)
	{
		npc->Render();
	}
}
