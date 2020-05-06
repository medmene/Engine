#include "Game_sources/include/LevelController.h"
#include "Game_sources/include/GameWindow.h"
#include "Game_sources/include/Menu.h"
#include "Game_sources/include/Level1.h"
#include "Game_sources/include/Level2.h"
#include "Game_sources/include/Level3.h"
#include "Game_sources/include/Level4.h"
#include "Game_sources/include/Level5.h"
#include "include/GameModeChangeController.h"


LevelController * LevelController::sm_instance = nullptr;

LevelController* LevelController::instance()
{
	if (!sm_instance)
	{
		sm_instance = new LevelController();
	}
	return sm_instance;
}

void LevelController::Init(SDL_Renderer* r, const Vector2& wSize)
{
	m_renderer = r;
	m_windowSize = wSize;
}

LevelController::LevelController()
	: m_currentState(UNDEFINED)
	, m_prevState(UNDEFINED)
{
	m_levels.resize(SIZE);
}

void LevelController::ChangeState(LevelState newState)
{
	if (m_currentState != newState)
	{
		m_prevState = m_currentState;
		m_currentState = newState;
		
		switch (m_currentState)
		{
		case MENU:
			m_levels[m_currentState] = new Menu();
			break;
		case LEVEL1:
			m_levels[m_currentState] = new Level1();
			break;
		case LEVEL2:
			m_levels[m_currentState] = new Level2();
			break;
		case LEVEL3:
			m_levels[m_currentState] = new Level3();
			break;
		case LEVEL4:
			m_levels[m_currentState] = new Level4();
			break;
		case LEVEL5:
			m_levels[m_currentState] = new Level5();
			break;
		}

		GameModeChangeController::instance()->StartHiding();
		std::thread th([this]() {
			m_levels[m_currentState]->Init(m_renderer, m_windowSize);
			m_skipFrame = 2;
			GameModeChangeController::instance()->StartShowing();
		});
		th.join();
	}
}

void LevelController::RunStartState()
{
	m_currentState = MENU;
	m_prevState = MENU;
	m_levels[m_currentState] = new Menu();
	m_levels[m_currentState]->Init(m_renderer, m_windowSize);
	m_skipFrame = -1;
	GameModeChangeController::instance()->StartShowing();
}

void LevelController::Update(float dt)
{
	if (m_skipFrame > 0)
	{
		m_levels[m_prevState]->Update(dt);
		m_skipFrame--;
		if (m_skipFrame == 0)
		{
			delete m_levels[m_prevState];
		}
	}

	if (m_levels[m_currentState] && m_levels[m_currentState]->m_loadingFinished)
	{
		m_levels[m_currentState]->Update(dt);
	}
}

void LevelController::Render()
{
	if (m_levels[m_currentState] && m_levels[m_currentState]->m_loadingFinished)
	{
		m_levels[m_currentState]->Render();
	}
}
