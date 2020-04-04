#include "Game_sources/include/Level1.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "Game_sources/include/GameWindow.h"


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

void Level1::Init(SDL_Renderer * renderer, const Vector2 & winSize)
{
	m_winSize = winSize;
	m_renderer = renderer;

	m_backgrounds.emplace_back(new GameObject(m_renderer, "grass2.png"));
	m_backgrounds.back()->UpdateSize(Vector2(m_winSize.x, m_winSize.y / 2));
	m_backgrounds.back()->UpdatePos(Vector2(0, 320));

	m_grounds.emplace_back(new GameObject(m_renderer, "sky.jpg"));
	m_grounds.back()->UpdateSize(Vector2(m_winSize.x, m_winSize.y / 2));
	m_grounds.back()->UpdatePos(Vector2(0, 0));
}

void Level1::Draw()
{
	for (auto & background : m_backgrounds)
	{
		GameWindow::instance()->DrawObject<GameObject>(background);
	}
	for (auto & ground : m_grounds)
	{
		GameWindow::instance()->DrawObject<GameObject>(ground);
	}
}
