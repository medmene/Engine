#include "Game_sources/include/GameInterface.h"
#include "include/GameObject.h"
#include "include/Button.h"



GameInterface::GameInterface(SDL_Renderer * r)
	: m_renderer(r)
	, m_visible(true) 
{
}

GameInterface::~GameInterface()
{
	for (auto && elem : m_elements)
	{
		delete elem;
	}
	m_elements.clear();
}

void GameInterface::Init()
{
	Button * btn = new Button(m_renderer, "infoBtn_settings", ResourceManager::GOBJECT);
	btn->SetStaticObject(true);
	btn->UpdatePos(Vector2(10, 10));
	m_elements.emplace_back(btn);
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
