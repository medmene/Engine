#include "Game_sources/include/Level2.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"
#include "include/EventPass.h"
#include "Game_sources/include/GameWindow.h"
#include "include/Player.h"


void Level2::Init(SDL_Renderer * renderer, const Vector2 & winSize)
{
	PassabilityMap::instance()->SetMap("passability2", ResourceManager::PMAP);
	GameWindow::instance()->GetPlayer()->GetGameObject()->UpdatePos({ 500,500 });
	
	m_winSize = winSize;
	m_renderer = renderer;

	float scale = 3;

	m_backgrounds.emplace_back(new GameObject(m_renderer, "lvl_2", ResourceManager::PNG));
	m_backgrounds.back()->UpdateSize(Vector2(scale * m_winSize.x, scale * m_winSize.y));
	m_backgrounds.back()->UpdatePos(Vector2(0, 0)); // for non static

	m_objects.emplace_back(new GameObject(m_renderer, "alien1", ResourceManager::GOBJECT));
	m_objects.back()->UpdateSize(Vector2(140, 140));
	m_objects.back()->UpdatePos(Vector2(720, 720));
	m_objects.back()->SetAnimationEnable(true);
	m_objects.back()->GetAnimator()->GetActiveAnimation()->Play();
	m_objects.emplace_back(new GameObject(m_renderer, "alien2", ResourceManager::GOBJECT));
	m_objects.back()->UpdateSize(Vector2(140, 140));
	m_objects.back()->UpdatePos(Vector2(600, 600));
	m_objects.back()->SetAnimationEnable(true);
	m_objects.back()->GetAnimator()->GetActiveAnimation()->Play();
}

Level2::~Level2()
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

	for (auto&& ev : m_buttons)
	{
		delete ev;
	}
	m_events.clear();
}

void Level2::Update(float dt)
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

void Level2::Render()
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
