#include "Game_sources/include/Level1.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"
#include "include/EventPass.h"
#include "Game_sources/include/GameWindow.h"
#include "include/Player.h"
#include "include/NPC.h"


void OpenDoorByButton(GameObject *o, Event *e)
{
	EventPass* ep = (EventPass*)e;
	EventPass::State s = ep->GetCurrentState();
	switch (s)
	{
	case EventPass::State::STAY_OUT:
		ep->SetCurrentState(EventPass::State::GET_IN);
		o->SetAnimationEnable(true);
		o->GetAnimator()->GetActiveAnimation()->Play();
		break;
	case EventPass::State::GET_IN:
		ep->SetCurrentState(EventPass::State::STAY_IN);
		//o->GetAnimator()->PlayAnimation("idle_open");
		//o->GetAnimator()->GetActiveAnimation()->Play();
		// o->SetAnimationEnable(false);
		break;
	case EventPass::State::STAY_IN:
		o->GetAnimator()->PlayAnimation("idle_open");
		break;
	case EventPass::State::GET_OUT: // ????
		break;
	default:
		break;
	}
}

void Level1::Init(SDL_Renderer * renderer, const Vector2 & winSize)
{
	PassabilityMap::instance()->SetMap("passability1", ResourceManager::PMAP);
	GameWindow::instance()->GetPlayer()->GetGameObject()->UpdatePos({ 530,1300 });

	m_winSize = winSize;
	m_renderer = renderer;

	float scale = 3, scaleDoor = 2;

	m_backgrounds.emplace_back(new GameObject(m_renderer, "lvl_1", ResourceManager::PNG));
	m_backgrounds.back()->UpdateSize(Vector2(scale * m_winSize.x, scale * m_winSize.y));
	//m_backgrounds.back()->SetStaticObject(true);
	m_backgrounds.back()->UpdatePos(Vector2(0, 0)); // for non static

	/*m_objects.emplace_back(new GameObject(m_renderer, "platform1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(200, 30));
	m_objects.back()->UpdatePos(Vector2(400, 200));*/

	Vector2 area{ 160 , 150}, pos{ 720 , 820};

	m_events.emplace_back(new EventPass());

	((EventPass*)m_events.back())->SetObject(GameWindow::instance()->GetPlayer()->GetGameObject());
	((EventPass*)m_events.back())->SetRect(pos, area + pos);

	m_objects.emplace_back(new GameObject(m_renderer, "wall", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(110, 150));
	m_objects.back()->UpdatePos(Vector2(750, 670));

	m_objects.emplace_back(new GameObject(m_renderer, "doors", ResourceManager::GOBJECT));
	m_objects.back()->UpdateSize(Vector2(160, 170));
	m_objects.back()->UpdatePos(Vector2(725, 710));
	m_objects.back()->Subscribe(m_events.back(),OpenDoorByButton);

	m_objects.emplace_back(new GameObject(m_renderer, "blue1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(90, 90));
	m_objects.back()->UpdatePos(Vector2(1537, 1000));
	
	// Initialize NPC
	m_npcs.emplace_back(new NPC(m_renderer, "alien1", ResourceManager::GOBJECT));
	m_npcs.back()->GetGameObject()->SetAnimationEnable(true);
	m_npcs.back()->GetGameObject()->GetAnimator()->GetActiveAnimation()->Play();
	m_npcs.back()->GetGameObject()->UpdatePos(Vector2(1480, 450));
	m_npcs.back()->GetGameObject()->UpdateSize(Vector2(100, 100));
	m_npcs.back()->Init();


	m_npcs.emplace_back(new NPC(m_renderer, "alien2", ResourceManager::GOBJECT));
	m_npcs.back()->GetGameObject()->SetAnimationEnable(true);
	m_npcs.back()->GetGameObject()->GetAnimator()->GetActiveAnimation()->Play();
	m_npcs.back()->GetGameObject()->UpdatePos(Vector2(2045, 1445));
	m_npcs.back()->GetGameObject()->UpdateSize(Vector2(100, 100));
	m_npcs.back()->Init();


	//m_npcs.emplace_back(new NPC(m_renderer, "npc1", ResourceManager::GOBJECT));
	//m_npcs.back()->GetGameObject()->SetAnimationEnable(true);
	//m_npcs.back()->GetGameObject()->GetAnimator()->GetActiveAnimation()->Play();
	//m_npcs.back()->GetGameObject()->UpdatePos(Vector2(750, 1000));
	//m_npcs.back()->GetGameObject()->UpdateColor(Color(50, 250, 50, 255));
	//m_npcs.back()->GetGameObject()->UpdateSize(Vector2(180, 180));
	//m_npcs.back()->Init();
}

Level1::~Level1()
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
	
	// for (auto&& ev : m_events)
	// {
	// 	delete ev;
	// }
	// m_events.clear();

	for (auto&& ev : m_npcs)
	{
		delete ev;
	}
	m_npcs.clear();
}

void Level1::Update(float dt)
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

void Level1::Render()
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
