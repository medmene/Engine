#include "Game_sources/include/Level5.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"
#include "Game_sources/include/GameWindow.h"
#include "include/NPC.h"
#include "include/Player.h"


void Level5::Init(SDL_Renderer * renderer, const Vector2 & winSize)
{
	PassabilityMap::instance()->SetMap("passability4", ResourceManager::PMAP);

	if (auto player = GameWindow::instance()->GetPlayer())
	{
		GameWindow::instance()->GetPlayer()->GetGameObject()->UpdatePos({ 230,1473 });
		player->SetVisible(true);
	}
	
	m_winSize = winSize;
	m_renderer = renderer;

	float scale = 3;

	m_objects.emplace_back(new GameObject(m_renderer, "lvl_4", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(scale * m_winSize.x, scale * m_winSize.y));
	m_objects.back()->UpdatePos(Vector2(0, 0)); // for non static

	m_objects.emplace_back(new GameObject(m_renderer, "blue1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(90, 90));
	m_objects.back()->UpdatePos(Vector2(491, 846));

	m_objects.emplace_back(new GameObject(m_renderer, "blue1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(90, 90));
	m_objects.back()->UpdatePos(Vector2(1359, 1394));
	
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

	m_objects.emplace_back(new GameObject(m_renderer, "blue1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(200, 200));
	m_objects.back()->UpdatePos(Vector2(2303, 1301));
	m_loadingFinished = true;
}