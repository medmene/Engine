#include "Game_sources/include/GameWindow.h"
#include "include/MouseInput.h"
#include "include/KeyboardInput.h"
#include "include/Camera.h"
#include "include/Label.h"


GameWindow * GameWindow::sm_instance = new GameWindow();

GameWindow::GameWindow()
{
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
	TTF_Init();

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
	// Init black background
	auto bg = SDL_CreateRGBSurface(0, m_windowSize.x, m_windowSize.y, 32, 0, 0, 0, 0);
	SDL_FillRect(bg, NULL, 0);
	m_bg = SDL_CreateTextureFromSurface(m_renderer, bg);
	m_bgRect = { 0, 0, (int)m_windowSize.x, (int)m_windowSize.y };
	if (bg)
	{
		SDL_FreeSurface(bg);
	}
}

GameWindow::~GameWindow()
{
	for (auto && gr : m_ground) 
	{
		delete gr;
	}
	m_ground.clear();

	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
	}
	if (m_window)
	{
		SDL_DestroyWindow(m_window);
	}
	if (m_bg)
	{
		SDL_DestroyTexture(m_bg);
	}
	if (m_someText)
	{
		delete m_someText;
	}

	delete Camera::instance();
	delete MouseInput::instance();
	delete KeyboardInput::instance();
}

SDL_Window* GameWindow::GetRawWindow()
{
	return m_window;
}

void GameWindow::Initialize()
{
	Camera::instance()->Initialize(Vector2(m_windowSize.x / 2, m_windowSize.y / 2));
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
	m_someText = new Label();
	m_someText->Init(m_renderer, "Just chill",Vector2(10, 10));
}

void GameWindow::Update()
{
	while (true)
	{
		////////////////  FPS     ////////////////
		FPS.UpdateFPS();
		cout << FPS.fps << "\n";

		////////////////  Events  ////////////////
		MouseInput::instance()->ResetDiffs();
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

		////////////////  Camera  ////////////////
		if (MouseInput::instance()->IsPressed(MouseInput::MOUSE_LEFT))
		{
			Camera::instance()->UpdatePos(MouseInput::instance()->GetDiff());
		}
		Camera::instance()->UpdateZoom(MouseInput::instance()->GetWheel());

		////////////////  Render  ////////////////
		SDL_RenderCopy(m_renderer, m_bg, nullptr, &m_bgRect);

		for (auto && ground : m_ground)
		{
			DrawObject<GameObject>(ground);
		}
		DrawObject<Label>(m_someText);

		SDL_RenderPresent(m_renderer);
	}
}

void GameWindow::DrawTexture(SDL_Texture * texture, const SDL_Rect & rect)
{
	if (texture) 
	{
		SDL_Rect localRect = rect;
		localRect.x *= Camera::instance()->GetZoom();
		localRect.y *= Camera::instance()->GetZoom();
		localRect.w *= Camera::instance()->GetZoom();
		localRect.h *= Camera::instance()->GetZoom();

		localRect.x += Camera::instance()->GetPosition().x;
		localRect.y += Camera::instance()->GetPosition().y;
		SDL_RenderCopy(m_renderer, texture, nullptr, &localRect);
	}
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
