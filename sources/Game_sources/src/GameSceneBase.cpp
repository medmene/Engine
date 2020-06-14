#include "Game_sources/include/GameSceneBase.h"
#include "include/GameObject.h"
#include "include/NPC.h"
#include "include/ResourceManager.h"
#include "pugixml/pugixml.hpp"
#include "include/Label.h"
#include "include/Button.h"



GameSceneBase::GameSceneBase(shared_ptr<WindowManager> wm)
	: Window(wm)
	, m_useSort(true)
{
	m_windowName = "level_base";
}

void GameSceneBase::LoadScene()
{
	auto resource = ResourceManager::instance()->GetResource(m_sceneName);

	if (resource) 
	{
		pugi::xml_document doc;
		doc.load_file(resource->GetPath().c_str());
		auto node = doc.child("game_scene");

		for (auto & object : node.children())
		{
			string type = object.name();
			auto parent = object.attribute("parent");

			if (type == "object") 
			{
				GameObject * gobj = new GameObject("empty");
				gobj->LoadGraphics(&object);
				auto isGround = object.attribute("ground");

				if (!isGround.empty() && strcmp(isGround.value(), "true") == 0)
				{
					m_groundObjects.emplace_back(gobj);
				}
				else 
				{
					m_objects.emplace_back(gobj);
				}

				// Set parent
				if (!parent.empty())
				{
					auto objPar = GetGameObject(parent.value());
					auto grndPar = GetGoundObject(parent.value());
					gobj->SetParent(objPar != nullptr ? objPar : grndPar);
				}
			}
			else if (type == "npc") 
			{
				NPC * npc = new NPC("empty");
				npc->LoadGraphics(&object);
				m_objects.emplace_back(npc);

				// Set parent
				if (!parent.empty())
				{
					auto objPar = GetGameObject(parent.value());
					auto grndPar = GetGoundObject(parent.value());
					npc->SetParent(objPar != nullptr ? objPar : grndPar);
				}
			}
			else if (type == "text_label")
			{
				Label * label = new Label("empty");
				label->LoadGraphics(&object);
				m_objects.emplace_back(label);

				// Set parent
				if (!parent.empty())
				{
					auto objPar = GetGameObject(parent.value());
					auto grndPar = GetGoundObject(parent.value());
					label->SetParent(objPar != nullptr ? objPar : grndPar);
				}
			}
			else if (type == "button")
			{
				Button * btn = new Button("empty");
				btn->LoadGraphics(&object);
				m_objects.emplace_back(btn);

				// Set parent
				if (!parent.empty())
				{
					auto objPar = GetGameObject(parent.value());
					auto grndPar = GetGoundObject(parent.value());
					btn->SetParent(objPar != nullptr ? objPar : grndPar);
				}
			}

			if (!m_objects.empty() && m_objects.back()->IsStaticObject())
			{
				auto pos = m_objects.back()->GetPosition();
				if (pos.x < 0)
				{
					pos.x = m_winSize.x + pos.x;
				}
				if (pos.y < 0)
				{
					pos.y = m_winSize.y + pos.y;
				}
				m_objects.back()->UpdatePos(pos);
			}
		}
	}
}

void GameSceneBase::Run()
{
	// TODO place here load scene
	Window::Run();
}

void GameSceneBase::Disappear()
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

void GameSceneBase::Update(float dt)
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

void GameSceneBase::Render()
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

GameObject * GameSceneBase::GetGameObject(const string & name)
{
	for (auto && obj : m_objects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	return nullptr;
}

GameObject * GameSceneBase::GetGoundObject(const string & name)
{
	for (auto && obj : m_groundObjects) 
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	return nullptr;
}

void GameSceneBase::AddObject(GameObject * obj)
{
	m_objects.emplace_back(obj);
}

bool GameSceneBase::SortComparer(const GameObject* lhs, const GameObject* rhs)
{
	return lhs->GetPivotPos().y < rhs->GetPivotPos().y;
}
