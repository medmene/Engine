#include "Game_sources/include/Level4.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"
#include "Game_sources/include/GameWindow.h"
#include "include/NPC.h"
#include "include/Player.h"


void Level4::Init(SDL_Renderer * renderer, const Vector2 & winSize)
{
	PassabilityMap::instance()->SetMap("passability3", ResourceManager::PMAP);
	
	if (auto player = GameWindow::instance()->GetPlayer())
	{
		GameWindow::instance()->GetPlayer()->GetGameObject()->UpdatePos({ 370,290 });
		player->SetVisible(true);
	}
	
	m_winSize = winSize;
	m_renderer = renderer;

	float scale = 3;

	m_objects.emplace_back(new GameObject(m_renderer, "lvl_3", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(scale * m_winSize.x, scale * m_winSize.y));
	m_objects.back()->UpdatePos(Vector2(0, 0)); // for non static

	m_objects.emplace_back(new GameObject(m_renderer, "blue1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(90, 90));
	m_objects.back()->UpdatePos(Vector2(1127, 950));

	m_objects.emplace_back(new GameObject(m_renderer, "blue1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(90, 90));
	m_objects.back()->UpdatePos(Vector2(1743, 753));


	//// Initialize NPC
	m_npcs.emplace_back(new NPC(m_renderer, "alien1", ResourceManager::GOBJECT));
	m_npcs.back()->GetGameObject()->SetAnimationEnable(true);
	m_npcs.back()->GetGameObject()->GetAnimator()->GetActiveAnimation()->Play();
	m_npcs.back()->GetGameObject()->UpdateColor(Color(250, 250, 50, 255));
	m_npcs.back()->GetGameObject()->UpdatePos(Vector2(2322, 452));
	m_npcs.back()->GetGameObject()->UpdateSize(Vector2(80, 80));
	m_npcs.back()->Init();

	m_npcs.emplace_back(new NPC(m_renderer, "alien1", ResourceManager::GOBJECT));
	m_npcs.back()->GetGameObject()->SetAnimationEnable(true);
	m_npcs.back()->GetGameObject()->GetAnimator()->GetActiveAnimation()->Play();
	m_npcs.back()->GetGameObject()->UpdateColor(Color(250, 10, 250, 255));
	m_npcs.back()->GetGameObject()->UpdatePos(Vector2(386, 1478));
	m_npcs.back()->GetGameObject()->UpdateSize(Vector2(90, 90));
	m_npcs.back()->Init();

	m_objects.emplace_back(new GameObject(m_renderer, "blue1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(200, 200));
	m_objects.back()->UpdatePos(Vector2(386, 1478));
	m_loadingFinished = true;
}