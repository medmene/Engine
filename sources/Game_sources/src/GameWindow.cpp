#include "Game_sources/include/GameWindow.h"
#include <iostream>
#include "include/MouseInput.h"
#include "include/KeyboardInput.h"
#include "include/Camera.h"
#include "include/Player.h"
#include "Game_sources/include/Menu.h"
#include "Game_sources/include/GameInterface.h"
#include "include/ResourceManager.h"
#include "include/PassabilityMap.h"
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
	delete ResourceManager::instance();

	delete m_player;

	if (m_renderer) { SDL_DestroyRenderer(m_renderer); }
	if (m_window) { SDL_DestroyWindow(m_window); }

	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

void GameWindow::Initialize()
{
	SoundManager::instance()->PlaySound(ResourceManager::instance()->
		GetResource("mainTheme", ResourceManager::MP3));
	Camera::instance()->Initialize(Vector2(m_windowSize.x / 2, m_windowSize.y * 0.75f));
	PassabilityMap::instance()->Init(m_renderer);

	m_player = new Player(m_renderer, "Player.gobj");
	m_player->SetVisible(false);
	
	m_windowManager = make_shared<WindowManager>(m_renderer, m_windowSize);
	m_windowManager->CreateAndRunWindow<Menu>();
	m_windowManager->CreateAndRunWindow<GameInterface>();
	m_windowManager->SetWindowLevel(GameInterface::GetName(), 15);
	
	Camera::instance()->SetFollowingObject(m_player);
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
	Camera::instance()->UpdateZoom(MouseInput::instance()->GetWheel());

	SoundManager::instance()->Update();
	PassabilityMap::instance()->Update();
	
	m_windowManager->Update(FPS.dt);
	Camera::instance()->Update(FPS.dt);
}

void GameWindow::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);

	m_windowManager->Render();
	PassabilityMap::instance()->Render();

	SDL_RenderPresent(m_renderer);
}