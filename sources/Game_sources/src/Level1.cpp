#include "Game_sources/include/Level1.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/ResourceManager.h"




void Level1::Init(SDL_Renderer * renderer, const Vector2 & winSize)
{
	m_winSize = winSize;
	m_renderer = renderer;

	m_backgrounds.emplace_back(new GameObject(m_renderer, "grass2", ResourceManager::PNG));
	m_backgrounds.back()->UpdateSize(Vector2(m_winSize.x, m_winSize.y / 2));
	m_backgrounds.back()->SetStaticObject(true);
	// m_backgrounds.back()->UpdatePos(Vector2(0, 160)); // for non static
	m_backgrounds.back()->UpdatePos(Vector2(0, 320)); // for static

	m_grounds.emplace_back(new GameObject(m_renderer, "sky", ResourceManager::JPG));
	m_grounds.back()->UpdateSize(Vector2(m_winSize.x, m_winSize.y / 2));
	m_grounds.back()->SetStaticObject(true);
	// m_grounds.back()->UpdatePos(Vector2(0, -160)); // for non static
	m_grounds.back()->UpdatePos(Vector2(0, 0)); // for non static

	m_objects.emplace_back(new GameObject(m_renderer, "platform1", ResourceManager::PNG));
	m_objects.back()->UpdateSize(Vector2(200, 30));
	m_objects.back()->UpdatePos(Vector2(400, 200));
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
}
