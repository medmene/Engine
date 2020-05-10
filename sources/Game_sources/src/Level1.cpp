#include "Game_sources/include/Level1.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/PassabilityMap.h"
#include "Game_sources/include/GameWindow.h"
#include "include/Player.h"
#include "include/NPC.h"


Level1::Level1(shared_ptr<WindowManager> wm)
	: LevelBase(wm)
{
	m_windowName = "level_1";
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

	m_objects.emplace_back(new GameObject("lvl_1.png"));
	m_objects.back()->UpdateSize(Vector2(scale * m_winSize.x, scale * m_winSize.y));
	m_objects.back()->UpdatePos(Vector2(0, 0));

	m_objects.emplace_back(new GameObject("wall.png"));
	m_objects.back()->UpdateSize(Vector2(110, 150));
	m_objects.back()->UpdatePos(Vector2(750, 670));

	m_objects.emplace_back(new GameObject("doors.gobj"));
	m_objects.back()->UpdateSize(Vector2(160, 170));
	m_objects.back()->UpdatePos(Vector2(725, 710));

	m_objects.emplace_back(new GameObject("blue1.png"));
	m_objects.back()->UpdateSize(Vector2(90, 90));
	m_objects.back()->UpdatePos(Vector2(1537, 1000));
	
	m_objects.emplace_back(new GameObject("blue1.png"));
	m_objects.back()->UpdateSize(Vector2(200, 200));
	m_objects.back()->UpdatePos(Vector2(2045, 1445));

	// Initialize NPC
	auto npc1 = new NPC("alien1.gobj");
	npc1->SetAnimationEnable(true);
	npc1->GetAnimator()->GetActiveAnimation()->Play();
	npc1->UpdatePos(Vector2(1480, 450));
	npc1->UpdateSize(Vector2(100, 100));
	npc1->Init();
	m_objects.emplace_back(npc1);

	auto npc2 = new NPC("alien2.gobj");
	npc2->SetAnimationEnable(true);
	npc2->GetAnimator()->GetActiveAnimation()->Play();
	npc2->UpdatePos(Vector2(2045, 1445));
	npc2->UpdateSize(Vector2(100, 100));
	npc2->Init();
	m_objects.emplace_back(npc2);

	m_objects.emplace_back(p);
	LevelBase::Run();
}
