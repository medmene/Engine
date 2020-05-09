#include "Game_sources/include/GameInterface.h"
#include "include/GameObject.h"
#include "include/Button.h"
#include "include/Label.h"



GameInterface::GameInterface(shared_ptr<WindowManager> w, SDL_Renderer * r, const Vector2 & wSize)
	: Window(w, r, wSize)
	, m_visible(true)
{
}

void GameInterface::Run()
{
	auto back = make_shared<GameObject>(m_renderer, "infoScroll_settings", ResourceManager::GOBJECT);
	back->SetStaticObject(true);
	back->UpdatePos(Vector2(45, 10));
	back->SetVisible(false);
	m_elements.emplace_back(back);
	
	auto btn = make_shared<Button>(m_renderer, "infoBtn_settings", ResourceManager::GOBJECT);
	btn->SetStaticObject(true);
	btn->UpdatePos(Vector2(10, 10));	
	btn->SetOnclick([this]()
	{
		for (auto && item : m_elements)
		{
			if (item->GetName() == "infoScroll_settings")
			{
				item->SetVisible(!item->IsVisible());
				return true;
			}
		}
		return false;
	});
	m_elements.emplace_back(btn);
	
	auto lbl = make_shared<Label>(m_renderer, "times", ResourceManager::TTF);
	lbl->Init("P-character area", 16);
	lbl->SetStaticObject(true);
	lbl->SetParent(back.get());
	lbl->SetFollowVisibility(true);
	lbl->UpdateRelativePos(Vector2(0, -60));
	lbl->UpdateColor(Color(0, 0, 0, 255));
	m_elements.emplace_back(lbl);
	
	auto lbl2 = make_shared<Label>(m_renderer, "times", ResourceManager::TTF);
	lbl2->Init("L-not passible map", 16);
	lbl2->SetStaticObject(true);
	lbl2->SetParent(back.get());
	lbl2->SetFollowVisibility(true);
	lbl2->UpdateRelativePos(Vector2(0, -40));
	lbl2->UpdateColor(Color(0, 0, 0, 255));
	m_elements.emplace_back(lbl2);

	auto lbl3 = make_shared<Label>(m_renderer, "times", ResourceManager::TTF);
	lbl3->Init("O-save map (with L)", 16);
	lbl3->SetStaticObject(true);
	lbl3->SetParent(back.get());
	lbl3->SetFollowVisibility(true);
	lbl3->UpdateRelativePos(Vector2(0, -20));
	lbl3->UpdateColor(Color(0, 0, 0, 255));
	lbl3->SetVisible(false);
	m_elements.emplace_back(lbl3);

	auto lbl4 = make_shared<Label>(m_renderer, "times", ResourceManager::TTF);
	lbl4->Init("J-music", 16);
	lbl4->SetStaticObject(true);
	lbl4->SetParent(back.get());
	lbl4->SetFollowVisibility(true);
	lbl4->UpdateRelativePos(Vector2(0, 0));
	lbl4->UpdateColor(Color(0, 0, 0, 255));
	m_elements.emplace_back(lbl4);

	auto lbl5 = make_shared<Label>(m_renderer, "times", ResourceManager::TTF);
	lbl5->Init("I-NPC way", 16);
	lbl5->SetStaticObject(true);
	lbl5->SetParent(back.get());
	lbl5->SetFollowVisibility(true);
	lbl5->UpdateRelativePos(Vector2(0, 20));
	lbl5->UpdateColor(Color(0, 0, 0, 255));
	m_elements.emplace_back(lbl5);

	auto lbl6 = make_shared<Label>(m_renderer, "times", ResourceManager::TTF);
	lbl6->Init("U - noclip", 16);
	lbl6->SetStaticObject(true);
	lbl6->SetParent(back.get());
	lbl6->SetFollowVisibility(true);
	lbl6->UpdateRelativePos(Vector2(0, 40));
	lbl6->UpdateColor(Color(0, 0, 0, 255));
	m_elements.emplace_back(lbl6);

	// ----------------------------------------------------------------------------------- //
	
	auto btnStngs = make_shared<Button>(m_renderer, "gameSettingsBtn_settings", ResourceManager::GOBJECT);
	btnStngs->SetStaticObject(true);
	btnStngs->UpdatePos(Vector2(m_winSize.x - btnStngs->GetSize().x - 10, 10));
	m_elements.emplace_back(btnStngs);
	Window::Run();
}

void GameInterface::Disappear()
{
	m_elements.clear();
}

void GameInterface::SetVisible(bool visible)
{
	if (visible != m_visible)
	{
		m_visible = visible;
		for (auto && elem : m_elements)
		{
			elem->SetVisible(m_visible);
		}
	}
}

void GameInterface::Update(float dt)
{
	for (auto && elem : m_elements)
	{
		elem->Update(dt);
	}
}

void GameInterface::Render()
{
	for (auto && elem : m_elements)
	{
		elem->Render();
	}
}
