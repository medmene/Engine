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
#include "Game_sources/include/GameInterface.h"
#include "Game_sources/include/Level2.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"
#include "include/EventManager.h"
#include "include/SoundManager.h"


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
	delete Camera::instance();
	delete MouseInput::instance();
	delete KeyboardInput::instance();
	delete PassabilityMap::instance();
	delete SoundManager::instance();
	delete EventManager::instance();
	delete ResourceManager::instance();

	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
	}

	if (m_window)
	{
		SDL_DestroyWindow(m_window);
	}

	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

void GameWindow::Initialize()
{
	SoundManager::instance()->PlaySound(ResourceManager::instance()->GetResource("mainTheme", ResourceManager::MP3));
	SoundManager::instance()->PauseAll();
	Camera::instance()->Initialize(Vector2(m_windowSize.x / 2, m_windowSize.y * 0.75f));
	PassabilityMap::instance()->Init(m_renderer);

	m_interface = new GameInterface(m_renderer, m_windowSize);
	m_interface->Init();
	
	m_player = new Player();
	m_player->Init(m_renderer);
	
	m_npc = new NPC();
	m_npc->Init(m_renderer, "npc1", ResourceManager::GOBJECT);

	// m_level1 = new Level1();
	// m_level1->Init(m_renderer, m_windowSize);

	// m_level2 = new Level2();
	// m_level2->Init(m_renderer, m_windowSize);

	m_menu = new Menu();
	m_menu->Init(m_renderer, m_windowSize);

	Camera::instance()->SetFollowingObject(m_player->GetGameObject());
}

void GameWindow::Update()
{
	while (true)
	{
		////////////////  FPS     ////////////////
		FPS.UpdateFPS();
		cout << FPS.fps << "\n";

		////////////////  Events  ////////////////SDL_KEYUP
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


		//////////////////////////////////////////
		////////////////  Update  ////////////////
		//////////////////////////////////////////

		//Camera::instance()->UpdateZoom(MouseInput::instance()->GetWheel());
		//m_level1->Update(FPS.dt);
		m_level2->Update(FPS.dt);
		m_player->Update(FPS.dt);
		m_npc->Update(FPS.dt);
		PassabilityMap::instance()->Update();
		Camera::instance()->Update(FPS.dt);
		EventManager::instance()->Update();
		SoundManager::instance()->Update();
		m_interface->Update(FPS.dt);

		
		//////////////////////////////////////////
		//////////////////////////////////////////
		//////////////////////////////////////////


		////////////////  Render  ////////////////
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
		SDL_RenderClear(m_renderer);

		//m_level1->Render();
		m_menu->Render();
		//m_level2->Render();

		m_player->Render();
		m_npc->Render();
		PassabilityMap::instance()->Render();
		m_interface->Render();
		
		SDL_RenderPresent(m_renderer);
	}
}