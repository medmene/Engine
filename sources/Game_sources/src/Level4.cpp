#include "Game_sources/include/Level4.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"
#include "include/EventPass.h"
#include "Game_sources/include/GameWindow.h"
#include "include/NPC.h"
#include "include/Player.h"


void Level4::Init(SDL_Renderer * renderer, const Vector2 & winSize)
{
	PassabilityMap::instance()->SetMap("passability4", ResourceManager::PMAP);
	GameWindow::instance()->GetPlayer()->GetGameObject()->UpdatePos({ 230,1473 });
	
	m_winSize = winSize;
	m_renderer = renderer;

	float scale = 3;
	//+		m_player->m_playerObject->m_position	{x=491.039825 y=846.234741 eps=9.99999975e-06 }	Vector2 item
	//+		m_player->m_playerObject->m_position	{x=1359.66602 y=1394.37244 eps=9.99999975e-06 }	Vector2 item
//+		m_player->m_playerObject->m_position	{x=2161.99048 y=366.014282 eps=9.99999975e-06 }	Vector2 npc
	//+		m_player->m_playerObject->m_position	{x=2303.83252 y=1301.49622 eps=9.99999975e-06 }	Vector2 npc

	m_backgrounds.emplace_back(new GameObject(m_renderer, "lvl_4", ResourceManager::PNG));
	m_backgrounds.back()->UpdateSize(Vector2(scale * m_winSize.x, scale * m_winSize.y));
	m_backgrounds.back()->UpdatePos(Vector2(0, 0)); // for non static

	m_objects.emplace_back(new GameObject(m_renderer, "blue1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(90, 90));
	m_objects.back()->UpdatePos(Vector2(491, 846));

	m_objects.emplace_back(new GameObject(m_renderer, "blue1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(90, 90));
	m_objects.back()->UpdatePos(Vector2(1359, 1394));


	//m_objects.emplace_back(new GameObject(m_renderer, "blue1", ResourceManager::PNG));
	//m_objects.back()->UpdateSize(Vector2(90, 90));
	//m_objects.back()->UpdatePos(Vector2(1537, 1000));

	//// Initialize NPC
	m_npcs.emplace_back(new NPC(m_renderer, "alien1", ResourceManager::GOBJECT));
	m_npcs.back()->GetGameObject()->SetAnimationEnable(true);
	m_npcs.back()->GetGameObject()->GetAnimator()->GetActiveAnimation()->Play();
	m_npcs.back()->GetGameObject()->UpdateColor(Color(50, 90, 50, 255));
	m_npcs.back()->GetGameObject()->UpdatePos(Vector2(2303, 1301));
	m_npcs.back()->GetGameObject()->UpdateSize(Vector2(80, 80));
	m_npcs.back()->Init();

	m_npcs.emplace_back(new NPC(m_renderer, "alien1", ResourceManager::GOBJECT));
	m_npcs.back()->GetGameObject()->SetAnimationEnable(true);
	m_npcs.back()->GetGameObject()->GetAnimator()->GetActiveAnimation()->Play();
	m_npcs.back()->GetGameObject()->UpdateColor(Color(90, 10, 50, 255));
	m_npcs.back()->GetGameObject()->UpdatePos(Vector2(2161, 366));
	m_npcs.back()->GetGameObject()->UpdateSize(Vector2(90, 90));
	m_npcs.back()->Init();
}

Level4::~Level4()
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

void Level4::Update(float dt)
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

void Level4::Render()
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
