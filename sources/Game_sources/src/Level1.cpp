#include "Game_sources/include/Level1.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/PassabilityMap.h"
#include "Game_sources/include/GameWindow.h"
#include "include/Player.h"
#include "include/NPC.h"
#include "include/BehaviourController.h"


Level1::Level1(shared_ptr<WindowManager> wm)
	: LevelBase(wm)
{
	m_windowName = "level_1";
}

void Level1::Run()
{
	PassabilityMap::instance()->SetMap("passability1.pmap");

	m_groundObjects.emplace_back(new GameObject("level1_back_settings.gobj"));
	m_groundObjects.back()->UpdateSize(Vector2(1600,1200));
	m_groundObjects.back()->UpdatePos(Vector2(0, 0));
	
	// Initialize NPC
	auto npc1 = new NPC("alien1.gobj");
	npc1->SetAnimationEnable(true);
	npc1->GetAnimator()->GetActiveAnimation()->Play();
	npc1->UpdatePos(Vector2(1200, 300));
	npc1->UpdateSize(Vector2(100, 100));
	npc1->GetBehviourController()->SetAnchorPoint(Vector2(1200, 300));
	npc1->GetBehviourController()->SetAnchorArea(Vector2(8, 8));
	m_objects.emplace_back(npc1);
	
	auto npc2 = new NPC("alien2.gobj");
	npc2->SetAnimationEnable(true);
	npc2->GetAnimator()->GetActiveAnimation()->Play();
	npc2->UpdatePos(Vector2(600, 1000));
	npc2->UpdateSize(Vector2(100, 100));
	npc2->GetBehviourController()->SetAnchorPoint(Vector2(600, 1000));
	npc2->GetBehviourController()->SetAnchorArea(Vector2(8, 8));
	m_objects.emplace_back(npc2);

	if (auto player = GameWindow::instance()->GetPlayer())
	{
		player->UpdatePos({ 530,300 });
		player->SetVisible(true);
		pl = player;
		m_objects.emplace_back(pl);
	}
	LevelBase::Run();
}
