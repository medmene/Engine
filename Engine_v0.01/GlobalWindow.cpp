#include "GlobalWindow.h"
#include "sGameObjectDisplay.h"
#include "Geometry.h"
#include "Renderer.h"
#include "sGameObject.h"


GlobalWindow::GlobalWindow()
{
	SDL_GetDesktopDisplayMode(0, &m_displayMode);
	m_windowSize = sVector2(960, 640);
	m_window = SDL_CreateWindow(
		"Window",								// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		m_windowSize.get_x_int(),					// width, in pixels
		m_windowSize.get_y_int(),					// height, in pixels
		0//SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN   // flags - see below
	);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		//SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//DefaultBackground();
}

GlobalWindow::GlobalWindow(bool fullScreeen)
{
	SDL_GetDesktopDisplayMode(0, &m_displayMode);
	m_windowSize = sVector2(m_displayMode.w, m_displayMode.h);
	if (fullScreeen)
	{
		m_window = SDL_CreateWindow(
			"Window",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			m_windowSize.get_x_int(), m_windowSize.get_y_int(),
			SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);
		m_renderer = SDL_CreateRenderer(m_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		DefaultBackground();
	}
	else
	{
		GlobalWindow();
	}
}

GlobalWindow::GlobalWindow(const sVector2& size)
{
	SDL_GetDesktopDisplayMode(0, &m_displayMode);
	m_windowSize = size;
	m_window = SDL_CreateWindow("Window",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		m_windowSize.get_x_int(), m_windowSize.get_y_int(),
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	DefaultBackground();
}


GlobalWindow::~GlobalWindow()
{
	if (m_window)
	{
		SDL_DestroyWindow(m_window);
	}
	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
	}
}

SDL_Window* GlobalWindow::GetRawWindow()
{
	return m_window;
}

void GlobalWindow::Initialize()
{
	m_root = new sGameObject(nullptr);
	m_root->SetRenderer(m_renderer);
	m_root->SetObjectDisplay(make_shared<sGameObjectDisplay>(m_root, SDL_GetWindowSurface(m_window)));
	
	m_gameObject = new sGameObject(m_root);
	m_gameObject->SetGroupId(1);
	m_gameObject->SetObjectDisplay(make_shared<sGameObjectDisplay>(m_gameObject, "game_source/test.jpg"));
	m_gameObject->GetGeometry()->SetBoundingBox(
		sBoundingBox(sVector3(100, 100, 0), sVector3(300, 300, 0)));
}

void GlobalWindow::DefaultBackground()
{
	if (m_renderer)
	{
		for (int x = 0; x < m_windowSize.get_x_int(); x += 1)
		{
			for (int y = 0; y < m_windowSize.get_y_int(); y += 1)
			{
				SDL_SetRenderDrawColor(m_renderer, 
					200 - y * 120/ m_windowSize.get_x_int(),
					y * 255 / m_windowSize.get_y_int(),
					x * 255 / m_windowSize.get_x_int(),
					255);
				SDL_RenderDrawPoint(m_renderer, x, y);
			}
		}		
		
		SDL_RenderPresent(m_renderer);
	}
}

int GlobalWindow::ProcessEvents(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_QUIT:
		return -1;
	}
	DefaultBackground();
	m_gameObject->GetRenderer()->render();

	return 1;
}
