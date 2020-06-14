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
	: GameSceneBase(wm)
{
	m_windowName = "level_1";
}

void Level1::LoadScene()
{
	m_sceneName = "level1.gscn";
	GameSceneBase::LoadScene();
}

void Level1::Run()
{
	PassabilityMap::instance()->SetMap("passability1.pmap");

	if (auto tmp = GetGameObject("Alien1"))
	{
		NPC* npc1 = dynamic_cast<NPC*>(tmp); 
		npc1->SetAnimationEnable(true);
		npc1->GetAnimator()->GetActiveAnimation()->Play();
		npc1->GetBehviourController()->SetupDefaultSettings();
	}

	if (auto tmp = GetGameObject("Alien2"))
	{
		NPC* npc2 = dynamic_cast<NPC*>(tmp);
		npc2->SetAnimationEnable(true);
		npc2->GetAnimator()->GetActiveAnimation()->Play();
		npc2->GetBehviourController()->SetupDefaultSettings();
	}

	if (auto player = GameWindow::instance()->GetPlayer())
	{
		player->UpdatePos(Vector2(530, 300));
		player->SetVisible(true);
		AddObject(player);
	}

	GameSceneBase::Run();
}
