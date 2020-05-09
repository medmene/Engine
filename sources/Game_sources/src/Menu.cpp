#include "Game_sources/include/Menu.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"
#include "Game_sources/include/GameWindow.h"
#include "include/Player.h"
#include "include/Button.h"
#include "Game_sources/include/Level1.h"


Menu::Menu(shared_ptr<WindowManager> wm, SDL_Renderer *r, const Vector2 & winSize)
	: LevelBase(wm, r, winSize)
{
}

void Menu::Run()
{
	PassabilityMap::instance()->SetMap("passability2", ResourceManager::PMAP);

	m_objects.emplace_back(new GameObject(m_renderer, "menu", ResourceManager::JPG));
	m_objects.back()->SetStaticObject(true);
	m_objects.back()->UpdateSize(Vector2(m_winSize.x, m_winSize.y));
	m_objects.back()->UpdatePos(Vector2(0, 0));

	float bSizeX = 200, bSizeY = 50, bPosX = m_winSize.x / 2 - bSizeX / 2;

	Button* btn = new Button(m_renderer, "button_menu", ResourceManager::GOBJECT);
	btn->SetStaticObject(true);
	btn->UpdateSize(Vector2(bSizeX, bSizeY));
	btn->UpdatePos(Vector2(bPosX, 100));
	btn->SetLabel("Start", 30, "calibri", ResourceManager::TTF);
	btn->SetOnclick([this]() {
		GameWindow::instance()->GetWindowManager()->CreateAndRunWindow<Level1>();
		this->Stop();
		return true;
	});
	m_objects.emplace_back(btn);

	Button* btn2 = new Button(m_renderer, "button_menu", ResourceManager::GOBJECT);
	btn2->SetStaticObject(true);
	btn2->UpdateSize(Vector2(bSizeX, bSizeY));
	btn2->UpdatePos(Vector2(bPosX, 300));
	btn2->SetLabel("Exit", 30, "calibri", ResourceManager::TTF);
	btn2->SetOnclick([]() { exit(0); return true; });
	m_objects.emplace_back(btn2);
	LevelBase::Run();
}
