#include "Game_sources/include/GameInterface.h"
#include "include/GameObject.h"
#include "include/Button.h"
#include "include/Label.h"



GameInterface::GameInterface(shared_ptr<WindowManager> w)
	: GameSceneBase(w)
	, m_visible(true)
{
	m_windowName = "game_interface";
}

void GameInterface::LoadScene()
{
	m_sceneName = "interface.gscn";
	GameSceneBase::LoadScene();
}

void GameInterface::Run()
{
	if (auto tmp = GetGameObject("infoBtn"))
	{
		Button* btn = dynamic_cast<Button*>(tmp);
		btn->SetOnclick([this]()
		{
			for (auto && item : m_objects)
			{
				if (item->GetName() == "infoScroll")
				{
					item->SetVisible(!item->IsVisible());
					return true;
				}
			}
			return false;
		});
	}

	GameSceneBase::Run();
}

void GameInterface::SetVisible(bool visible)
{
	if (visible != m_visible)
	{
		m_visible = visible;
		for (auto && obj : m_objects)
		{
			obj->SetVisible(m_visible);
		}
	}
}
