#include "Game_sources/include/Menu.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"
#include "include/EventPass.h"
#include "Game_sources/include/GameWindow.h"
#include "include/Player.h"


void Menu::Init(SDL_Renderer * renderer, const Vector2 & winSize)
{
	PassabilityMap::instance()->SetMap("passability2", ResourceManager::PMAP);
	GameWindow::instance()->GetPlayer()->GetGameObject()->UpdatePos({ 500,500 });
	
	m_winSize = winSize;
	m_renderer = renderer;

	m_backgrounds.emplace_back(new GameObject(m_renderer, "menu", ResourceManager::JPG));
	m_backgrounds.back()->SetStaticObject(true);
	m_backgrounds.back()->UpdateSize(Vector2(m_winSize.x, m_winSize.y));
	m_backgrounds.back()->UpdatePos(Vector2(0, 0));

	float bSizeX = 200, bSizeY = 50, bPosX = m_winSize.x / 2 - bSizeX / 2;

	m_buttons.emplace_back(new Button(m_renderer, "button_menu", ResourceManager::GOBJECT));
	m_buttons.back()->SetStaticObject(true);
	m_buttons.back()->UpdateSize(Vector2(bSizeX, bSizeY));
	m_buttons.back()->UpdatePos(Vector2(bPosX, 150));
	m_buttons.back()->SetLabel("Start", 30, "calibri", ResourceManager::TTF);

	m_buttons.emplace_back(new Button(m_renderer, "button_menu", ResourceManager::GOBJECT));
	m_buttons.back()->SetStaticObject(true);
	m_buttons.back()->UpdateSize(Vector2(bSizeX, bSizeY));
	m_buttons.back()->UpdatePos(Vector2(bPosX, 300));
	m_buttons.back()->SetLabel("Exit", 30, "calibri", ResourceManager::TTF);
}

Menu::~Menu()
{
	for (auto && bg : m_backgrounds)
	{
		delete bg;
	}
	m_backgrounds.clear();

	for (auto && gr : m_grounds)
	{
		delete gr;
	}
	m_grounds.clear();

	for (auto && obj : m_objects)
	{
		delete obj;
	}
	m_objects.clear();

	for (auto&& obj : m_buttons)
	{
		delete obj;
	}
	m_buttons.clear();

	for (auto&& ev : m_events)
	{
		delete ev;
	}
	m_events.clear();
}

void Menu::Update(float dt)
{
	for (auto && background : m_backgrounds)
	{
		background->Update(dt);
	}
	
	for (auto && ground : m_grounds)
	{
		ground->Update(dt);
	}

	for (auto && object : m_objects)
	{
		object->Update(dt);
	}

	for (auto && object : m_buttons)
	{
		object->Update(dt);
	}
}

void Menu::Render()
{
	for (auto && background : m_backgrounds)
	{
		background->Render();
	}
	
	for (auto && ground : m_grounds)
	{
		ground->Render();
	}

	for (auto && object : m_objects)
	{
		object->Render();
	}

	for (auto&& object : m_buttons)
	{
		object->Render();
	}
}
