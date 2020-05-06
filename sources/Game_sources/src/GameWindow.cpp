#include "Game_sources/include/GameWindow.h"
#include <iostream>
#include "include/MouseInput.h"
#include "include/KeyboardInput.h"
#include "include/Camera.h"
#include "include/Label.h"
#include "include/Player.h"
#include "include/NPC.h"
#include "include/GameObject.h"
#include "Game_sources/include/Menu.h"
#include "Game_sources/include/Level1.h"
#include "Game_sources/include/Level2.h"
#include "Game_sources/include/Level3.h"
#include "Game_sources/include/Level4.h"
#include "Game_sources/include/Level5.h"
#include "Game_sources/include/GameInterface.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"
#include "include/SoundManager.h"
#include "include/GameModeChangeController.h"
#include "Game_sources/include/Level5.h"
#include "Game_sources/include/LevelController.h"

GameWindow * GameWindow::sm_instance = new GameWindow();

GameWindow::GameWindow()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	SDL_GetDesktopDisplayMode(0, &m_displayMode);
	m_windowSize = Vector2(960, 640);
	m_window = SDL_CreateWindow(
		"Window",									// window title
		SDL_WINDOWPOS_UNDEFINED,						// initial x position
		SDL_WINDOWPOS_UNDEFINED,						// initial y position
		m_windowSize.x,								// width, in pixels
		m_windowSize.y,								// height, in pixels
		0 //SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN	// flags - see below
	);
	
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
}

GameWindow::~GameWindow()
{
	delete GameModeChangeController::instance();
	delete Camera::instance();
	delete MouseInput::instance();
	delete KeyboardInput::instance();
	delete PassabilityMap::instance();
	delete SoundManager::instance();
	delete ResourceManager::instance();

	// delete m_menu;
	// delete m_level1;
	// delete m_level2;
	// delete m_level3;
	// delete m_level4;
	// delete m_level5;
	delete m_player;
	delete m_interface;

	if (m_renderer) { SDL_DestroyRenderer(m_renderer); }
	if (m_window) { SDL_DestroyWindow(m_window); }

	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

void GameWindow::Initialize()
{
	GameModeChangeController::instance()->Init(m_renderer, m_windowSize);
	LevelController::instance()->Init(m_renderer, m_windowSize);
	SoundManager::instance()->PlaySound(ResourceManager::instance()->
		GetResource("mainTheme", ResourceManager::MP3));
	Camera::instance()->Initialize(Vector2(m_windowSize.x / 2, m_windowSize.y * 0.75f));
	PassabilityMap::instance()->Init(m_renderer);

	m_interface = new GameInterface(m_renderer, m_windowSize);
	m_interface->Init();
	
	m_player = new Player(m_renderer);
	m_player->SetVisible(false);
	
	LevelController::instance()->RunStartState();
	Camera::instance()->SetFollowingObject(m_player->GetGameObject());
}

void GameWindow::Processing()
{
	while (true)
	{
		////////////////   FPS    ////////////////
		FPS.UpdateFPS();
		cout << FPS.fps << "\n";

		////////////////  Events  ////////////////
		MouseInput::instance()->ResetDiffs();
		KeyboardInput::instance()->Reset();
		SDL_Event * e = new SDL_Event();
		
		if (SDL_PollEvent(e))
		{
			MouseInput::instance()->Update(e);
			KeyboardInput::instance()->Update(e);
			
			if (e->type == SDL_QUIT)
				break;
			else if (e->type == SDL_KEYUP && e->key.keysym.sym == SDLK_ESCAPE)
				break;
		}
		delete e;

		////////////////  Update  ////////////////
		Update();

		////////////////  Render  ////////////////
		Render();
	}
}

void GameWindow::Update()
{
	//Camera::instance()->UpdateZoom(MouseInput::instance()->GetWheel());

	LevelController::instance()->Update(FPS.dt);
	m_player->Update(FPS.dt);
	GameModeChangeController::instance()->Update(FPS.dt);
	PassabilityMap::instance()->Update();
	Camera::instance()->Update(FPS.dt);
	SoundManager::instance()->Update();
	m_interface->Update(FPS.dt);
}

void GameWindow::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);
	
	LevelController::instance()->Render();
	PassabilityMap::instance()->Render();
	m_player->Render();
	m_interface->Render();
	GameModeChangeController::instance()->Render();

	SDL_RenderPresent(m_renderer);
}