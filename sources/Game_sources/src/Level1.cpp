#include "Game_sources/include/Level1.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/Animator.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"




void Level1::Init(SDL_Renderer * renderer, const Vector2 & winSize)
{
	PassabilityMap::instance()->SetMap("passability", ResourceManager::PMAP);
	
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

	m_buttons.emplace_back(new Button(m_renderer, "button1", ResourceManager::GOBJECT));
	m_buttons.back()->SetStaticObject(false);
	m_buttons.back()->UpdateSize(Vector2(20, 20));
	m_buttons.back()->UpdatePos(Vector2(700, 1000));

	m_objects.emplace_back(new GameObject(m_renderer, "doors", ResourceManager::GOBJECT));
	m_objects.back()->UpdateSize(Vector2(scaleDoor * 70, scaleDoor * 70));
	m_objects.back()->UpdatePos(Vector2(scale * 240, scale * 245));
	m_objects.back()->SetAnimationEnable(true);
	m_objects.back()->GetAnimator()->GetActiveAnimation()->Play();
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
}

void Level1::Update(float dt)
{
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
}
