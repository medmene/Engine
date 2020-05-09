#include "Game_sources/include/Level1.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"
#include "Game_sources/include/GameWindow.h"
#include "include/Player.h"
#include "include/NPC.h"


Level1::Level1(shared_ptr<WindowManager> wm, SDL_Renderer * renderer, const Vector2 & winSize)
	: LevelBase(wm, renderer, winSize)
{
}

void Level1::Run()
{
	PassabilityMap::instance()->SetMap("passability1.pmap");
	if (auto player = GameWindow::instance()->GetPlayer())
	{
		p = GameWindow::instance()->GetPlayer();
		p->UpdatePos({ 530,1300 });
		player->SetVisible(true);
	}

	float scale = 3;

	m_objects.emplace_back(new GameObject(m_renderer, "lvl_1.png"));
	m_objects.back()->UpdateSize(Vector2(scale * m_winSize.x, scale * m_winSize.y));
	m_objects.back()->UpdatePos(Vector2(0, 0));

	m_objects.emplace_back(new GameObject(m_renderer, "wall.png"));
	m_objects.back()->UpdateSize(Vector2(110, 150));
	m_objects.back()->UpdatePos(Vector2(750, 670));

	m_objects.emplace_back(new GameObject(m_renderer, "doors.gobj"));
	m_objects.back()->UpdateSize(Vector2(160, 170));
	m_objects.back()->UpdatePos(Vector2(725, 710));

	m_objects.emplace_back(new GameObject(m_renderer, "blue1.png"));
	m_objects.back()->UpdateSize(Vector2(90, 90));
	m_objects.back()->UpdatePos(Vector2(1537, 1000));

	// Initialize NPC
	m_npcs.emplace_back(new NPC(m_renderer, "alien1.gobj"));
	m_npcs.back()->SetAnimationEnable(true);
	m_npcs.back()->GetAnimator()->GetActiveAnimation()->Play();
	m_npcs.back()->UpdatePos(Vector2(1480, 450));
	m_npcs.back()->UpdateSize(Vector2(100, 100));
	m_npcs.back()->Init();


	m_npcs.emplace_back(new NPC(m_renderer, "alien2.gobj"));
	m_npcs.back()->SetAnimationEnable(true);
	m_npcs.back()->GetAnimator()->GetActiveAnimation()->Play();
	m_npcs.back()->UpdatePos(Vector2(2045, 1445));
	m_npcs.back()->UpdateSize(Vector2(100, 100));
	m_npcs.back()->Init();

	m_objects.emplace_back(new GameObject(m_renderer, "blue1.png"));
	m_objects.back()->UpdateSize(Vector2(200, 200));
	m_objects.back()->UpdatePos(Vector2(2045, 1445));
	m_objects.emplace_back(p);
	LevelBase::Run();
}
