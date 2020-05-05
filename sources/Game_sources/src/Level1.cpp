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

	float scale = 3;

	m_objects.emplace_back(new GameObject(m_renderer, "lvl_1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(scale * m_winSize.x, scale * m_winSize.y));
	m_objects.back()->UpdatePos(Vector2(0, 0));
	
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

	m_events.emplace_back(new EventPass());
	((EventPass*)m_events.back())->SetObject(GameWindow::instance()->GetPlayer()->GetGameObject());
	((EventPass*)m_events.back())->SetRect({ 2045, 1445 }, Vector2{ 2045, 1445 } +Vector2{200, 200});

	m_objects.emplace_back(new GameObject(m_renderer, "blue1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(200, 200));
	m_objects.back()->UpdatePos(Vector2(2045, 1445));
	m_objects.back()->Subscribe(m_events.back(), [](GameObject* o, Event* e) {GameWindow::instance()->ChangeState(GameWindow::LEVEL2); });
}
