#include "../sources/Game_sources/include/GameWindow.h"


GameWindow * GameWindow::sm_instance = new GameWindow();

GameWindow::GameWindow()
{
	SDL_GetDesktopDisplayMode(0, &m_displayMode);
	m_windowSize = sVector2(960, 640);
	m_window = SDL_CreateWindow(
		"Window",									// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		m_windowSize.get_x_int(),					// width, in pixels
		m_windowSize.get_y_int(),					// height, in pixels
		0 //SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN	// flags - see below
	);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	//SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

//GameWindow::GameWindow(bool fullScreeen)
//{
//	SDL_GetDesktopDisplayMode(0, &m_displayMode);
//	m_windowSize = sVector2(m_displayMode.w, m_displayMode.h);
//	if (fullScreeen)
//	{
//		m_window = SDL_CreateWindow(
//			"Window",
//			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//			m_windowSize.get_x_int(), m_windowSize.get_y_int(),
//			SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);
//	}
//	else
//	{
//		GameWindow();
//	}
//}
//
//GameWindow::GameWindow(const sVector2& size)
//{
//	SDL_GetDesktopDisplayMode(0, &m_displayMode);
//	m_windowSize = size;
//	m_window = SDL_CreateWindow("Window",
//		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//		m_windowSize.get_x_int(), m_windowSize.get_y_int(),
//		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
//}

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
}

SDL_Window* GameWindow::GetRawWindow()
{
	return m_window;
}

void GameWindow::Initialize()
{
	m_root = new sGameObject(nullptr);
	m_root->SetObjectDisplay(make_shared<sGameObjectDisplay>(m_renderer, m_root, SDL_GetWindowSurface(m_window)));

	m_gameObject = new sGameObject(m_root);
	m_gameObject->SetObjectDisplay(make_shared<sGameObjectDisplay>(m_renderer, 
		m_gameObject, "resources/test_png.png"));
	m_gameObject->GetGeometry()->SetBoundingBox(
		sBoundingBox(sVector3(100, 100, 0), sVector3(300, 300, 0)));
}


int GameWindow::ProcessEvents()
{
	while (true)
	{
		SDL_Event e;
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
		}
		DrawTexture(m_root);
		DrawTexture(m_gameObject);
		SDL_RenderPresent(m_renderer);
	}
	return 1;
}

void GameWindow::Update()
{

}

void GameWindow::DrawTexture(sGameObject * obj)
{
	SDL_RenderCopy(m_renderer, obj->GetObjectDisplay()->GetTexture(),
		NULL, &obj->GetGeometry()->m_rect);
	/*SDL_RenderCopyEx(SDL_Renderer*          renderer,
			SDL_Texture*           texture,
			const SDL_Rect*        srcrect,
			const SDL_Rect*        dstrect,
			const double           angle,
			const SDL_Point*       center,
			const SDL_RendererFlip flip)*/
}
