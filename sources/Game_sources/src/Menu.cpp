#include "Game_sources/include/Menu.h"
#include "include/Label.h"
#include "include/GameObject.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"
#include "Game_sources/include/GameWindow.h"
#include "include/Button.h"
#include "Game_sources/include/Level1.h"


Menu::Menu(shared_ptr<WindowManager> wm)
	: LevelBase(wm)
{
	m_windowName = "game_menu";
	m_useSort = false;
}

void Menu::Run()
{
	LevelBase::Run();
}
