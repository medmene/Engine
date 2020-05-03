#include "Game_sources/include/Level2.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"
#include "include/EventPass.h"
#include "Game_sources/include/GameWindow.h"
#include "include/NPC.h"
#include "include/Player.h"


void Level2::Init(SDL_Renderer * renderer, const Vector2 & winSize)
{
	PassabilityMap::instance()->SetMap("passability2", ResourceManager::PMAP);
	GameWindow::instance()->GetPlayer()->GetGameObject()->UpdatePos({ 475,280 });
	
	m_winSize = winSize;
	m_renderer = renderer;

	float scale = 3;

	m_backgrounds.emplace_back(new GameObject(m_renderer, "lvl_2", ResourceManager::PNG));
	m_backgrounds.back()->UpdateSize(Vector2(scale * m_winSize.x, scale * m_winSize.y));
	m_backgrounds.back()->UpdatePos(Vector2(0, 0)); // for non static

	m_objects.emplace_back(new GameObject(m_renderer, "blue1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(90, 90));
	m_objects.back()->UpdatePos(Vector2(1749, 394));

	m_objects.emplace_back(new GameObject(m_renderer, "blue1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(90, 90));
	m_objects.back()->UpdatePos(Vector2(574, 1427));


	//+		m_player->m_playerObject->m_position	{x=981.162109 y=857.176514 eps=9.99999975e-06 }	Vector2 npc 1
//+		m_player->m_playerObject->m_position	{x=2249.90259 y=1517.14966 eps=9.99999975e-06 }	Vector2 npc2


	//m_objects.emplace_back(new GameObject(m_renderer, "blue1", ResourceManager::PNG));
	//m_objects.back()->UpdateSize(Vector2(90, 90));
	//m_objects.back()->UpdatePos(Vector2(1537, 1000));

	//// Initialize NPC
	m_npcs.emplace_back(new NPC(m_renderer, "alien1", ResourceManager::GOBJECT));
	m_npcs.back()->GetGameObject()->SetAnimationEnable(true);
	m_npcs.back()->GetGameObject()->GetAnimator()->GetActiveAnimation()->Play();
	m_npcs.back()->GetGameObject()->UpdateColor(Color(250, 10, 50, 255));
	m_npcs.back()->GetGameObject()->UpdatePos(Vector2(981, 857));
	m_npcs.back()->GetGameObject()->UpdateSize(Vector2(80, 80));
	m_npcs.back()->Init();

	m_npcs.emplace_back(new NPC(m_renderer, "alien1", ResourceManager::GOBJECT));
	m_npcs.back()->GetGameObject()->SetAnimationEnable(true);
	m_npcs.back()->GetGameObject()->GetAnimator()->GetActiveAnimation()->Play();
	m_npcs.back()->GetGameObject()->UpdateColor(Color(0, 10, 250, 255));
	m_npcs.back()->GetGameObject()->UpdatePos(Vector2(2249, 1517));
	m_npcs.back()->GetGameObject()->UpdateSize(Vector2(90, 90));
	m_npcs.back()->Init();
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

	for (auto&& ev : m_npcs)
	{
		delete ev;
	}
	m_npcs.clear();
}

void Level2::Update(float dt)
{
	for (auto&& npc : m_npcs)
	{
		npc->Update(dt);
	}

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

	for (auto&& npc : m_npcs)
	{
		npc->Render();
	}
}
