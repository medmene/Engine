#include "Game_sources/include/GameWindow.h"
#include "include/MouseInput.h"
#include "include/KeyboardInput.h"
#include "include/Camera.h"
#include "include/Label.h"
#include "include/Player.h"
#include "include/GameObject.h"
#include "Game_sources/include/Level1.h"
#include "include/ResourceManager.h"


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
}

GameWindow::~GameWindow()
{
	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
	}
	
	if (m_window)
	{
		SDL_DestroyWindow(m_window);
	}

	delete Camera::instance();
	delete MouseInput::instance();
	delete KeyboardInput::instance();
}

void GameWindow::Initialize()
{
	Camera::instance()->Initialize(Vector2(m_windowSize.x / 2, m_windowSize.y * 0.75f));

	m_level1 = new Level1();
	m_level1->Init(m_renderer, m_windowSize);

	m_player = new Player();
	m_player->Init(m_renderer, m_windowSize);
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
		m_level1->Update(FPS.dt);
		m_player->Update(FPS.dt);
		
		Camera::instance()->SetPos(m_player->GetGameObject()->GetCenterPos());

		//////////////////////////////////////////
		//////////////////////////////////////////
		//////////////////////////////////////////


		////////////////  Render  ////////////////
		SDL_RenderClear(m_renderer);

		m_level1->Draw();
		m_player->GetGameObject()->Draw();

		SDL_RenderPresent(m_renderer);
	}
}

//void GameWindow::DrawTexture(SDL_Texture * texture, const SDL_Rect & rect,
//	double angle, const SDL_Point & center, SDL_RendererFlip flip)
//{
//	SDL_RenderCopyEx(m_renderer, texture, nullptr, &rect, angle, &center, flip);
//
//	/*SDL_RenderCopyEx(SDL_Renderer*          renderer,
//			SDL_Texture*           texture,
//			const SDL_Rect*        srcrect,
//			const SDL_Rect*        dstrect,
//			const double           angle,
//			const SDL_Point*       center,
//			const SDL_RendererFlip flip)*/
//}
