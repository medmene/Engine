#include "Game_sources/include/GameWindow.h"
#include "include/MouseInput.h"
#include "include/KeyboardInput.h"

GameWindow * GameWindow::sm_instance = new GameWindow();

GameWindow::GameWindow()
{
	SDL_GetDesktopDisplayMode(0, &m_displayMode);
	m_windowSize = Vector2(960, 640);
	m_window = SDL_CreateWindow(
		"Window",									// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		m_windowSize.x,								// width, in pixels
		m_windowSize.y,								// height, in pixels
		0 //SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN	// flags - see below
	);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
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
	for (auto && gr : m_ground) 
	{
		delete gr;
	}
	m_ground.clear();
}

SDL_Window* GameWindow::GetRawWindow()
{
	return m_window;
}

void GameWindow::Initialize()
{
	for (int x = 0; x < 9; ++x)
	{
		for (int y = 0; y < 10; ++y)
		{
			GameObject * obj = new GameObject(m_renderer, "ground.png");
			obj->UpdateSize(Vector2(100, 60));
			obj->UpdatePos(Vector2(x * 101, y * 61));
			m_ground.emplace_back(obj);
		}
	}
}

void GameWindow::Update()
{
	while (true)
	{
		////////////////  FPS     ////////////////
		FPS.UpdateFPS();
		cout << FPS.fps << "\n";
		////////////////  Events  ////////////////
		SDL_Event e;
		if (SDL_PollEvent(&e))
		{
			MouseInput::instance()->Update(&e);
			KeyboardInput::instance()->Update(&e);
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
		}
		////////////////  Render  ////////////////
		for (auto && ground : m_ground)
		{
			DrawTexture(ground->GetTexture(), ground->GetRenderRect());
			//DrawTexture(ground->GetTexture(), ground->GetRenderRect(), ground->GetAngle(), ground->GetCenterPos());
		}
		SDL_RenderPresent(m_renderer);
	}
}

void GameWindow::DrawTexture(SDL_Texture * texture, const SDL_Rect & rect)
{
	SDL_RenderCopy(m_renderer, texture, nullptr, &rect);
}

void GameWindow::DrawTexture(SDL_Texture * texture, const SDL_Rect & rect,
	double angle, const SDL_Point & center, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(m_renderer, texture, nullptr, &rect, angle, &center, flip);

	/*SDL_RenderCopyEx(SDL_Renderer*          renderer,
			SDL_Texture*           texture,
			const SDL_Rect*        srcrect,
			const SDL_Rect*        dstrect,
			const double           angle,
			const SDL_Point*       center,
			const SDL_RendererFlip flip)*/
}
