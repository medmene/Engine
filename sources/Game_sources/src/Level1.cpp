#include "Game_sources/include/Level1.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"


void Level1::Init(SDL_Renderer * renderer, const Vector2 & winSize)
{
	PassabilityMap::instance()->SetMap("passabilitystart", ResourceManager::PMAP);
	
	m_winSize = winSize;
	m_renderer = renderer;

	float scale = 3;

	m_objects.emplace_back(new GameObject(m_renderer, "MadRoom", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(scale * m_winSize.x, scale * m_winSize.y));
	m_objects.back()->UpdatePos(Vector2(0, 0));
	m_loadingFinished = true;
}