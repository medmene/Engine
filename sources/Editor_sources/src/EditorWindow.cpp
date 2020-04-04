#include "Editor_sources/include/EditorWindow.h"
#include "include/MouseInput.h"
#include "include/KeyboardInput.h"
#include "include/Camera.h"
#include "Editor_sources/include/SettingsWidget.h"


EditorWindow * EditorWindow::sm_instance = new EditorWindow();

EditorWindow::EditorWindow()
{
	//SDL_GetDesktopDisplayMode(0, &m_displayMode);
	//m_windowSize = Vector2(960, 640);
	//m_window = SDL_CreateWindow(
	//	"Window",									// window title
	//	SDL_WINDOWPOS_UNDEFINED,					// initial x position
	//	SDL_WINDOWPOS_UNDEFINED,					// initial y position
	//	m_windowSize.x,								// width, in pixels
	//	m_windowSize.y,								// height, in pixels
	//	0 //SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN	// flags - see below
	//);
	//m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	//// Init black background
	//auto bg = SDL_CreateRGBSurface(0, m_windowSize.x, m_windowSize.y, 32, 0, 0, 0, 0);
	//SDL_FillRect(bg, NULL, 0);
	//m_bg = SDL_CreateTextureFromSurface(m_renderer, bg);
	//m_bgRect = { 0, 0, (int)m_windowSize.x, (int)m_windowSize.y };
	//SDL_FreeSurface(bg);
}

EditorWindow::~EditorWindow()
{
	/*if (m_renderer)
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
	if (m_bg)
	{
		SDL_DestroyTexture(m_bg);
	}
	m_ground.clear();*/
}

void EditorWindow::Initialize()
{
	/*Camera::instance()->Initialize(Vector2(m_windowSize.x / 2, m_windowSize.y / 2));
	m_settings = new SettingsWidget();
	m_settings->Init(this);*/
}

void EditorWindow::Update()
{
	//while (true)
	//{
	//	////////////////  FPS     ////////////////
	//	FPS.UpdateFPS();
	//	cout << FPS.fps << "\n";

	//	////////////////  Events  ////////////////
	//	MouseInput::instance()->ResetDiffs();
	//	SDL_Event e;
	//	if (SDL_PollEvent(&e))
	//	{
	//		MouseInput::instance()->Update(&e);
	//		KeyboardInput::instance()->Update(&e);
	//		if (e.type == SDL_QUIT)
	//			break;
	//		else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
	//			break;
	//	}

	//	////////////////  Camera  ////////////////
	//	Camera::instance()->UpdateZoom(MouseInput::instance()->GetWheel());
	//	if (MouseInput::instance()->IsPressed(MouseInput::MOUSE_LEFT))
	//	{
	//		Camera::instance()->UpdatePos(MouseInput::instance()->GetDiff());
	//	}

	//	////////////////  Render  ////////////////
	//	SDL_RenderCopy(m_renderer, m_bg, nullptr, &m_bgRect);

	//	m_settings->Draw();

	//	/*for (auto && ground : m_ground)
	//	{
	//		DrawObject(ground);
	//	}*/
	//	SDL_RenderPresent(m_renderer);
	//}
}

void EditorWindow::DrawObject(GameObject * object)
{
	/*if (object->IsVisible()) 
	{
		DrawTexture(object->GetTexture(), object->GetRenderRect());
	}*/
}

void EditorWindow::DrawTexture(SDL_Texture * texture, const SDL_Rect & rect)
{
	/*SDL_Rect localRect = rect;
	localRect.x *= Camera::instance()->GetZoom();
	localRect.y *= Camera::instance()->GetZoom();
	localRect.w *= Camera::instance()->GetZoom();
	localRect.h *= Camera::instance()->GetZoom();

	localRect.x += Camera::instance()->GetPosition().x;
	localRect.y += Camera::instance()->GetPosition().y;
	SDL_RenderCopy(m_renderer, texture, nullptr, &localRect);*/
}

void EditorWindow::DrawTexture(SDL_Texture * texture, const SDL_Rect & rect,
	double angle, const SDL_Point & center, SDL_RendererFlip flip)
{
	//SDL_RenderCopyEx(m_renderer, texture, nullptr, &rect, angle, &center, flip);

	/*SDL_RenderCopyEx(SDL_Renderer*          renderer,
			SDL_Texture*           texture,
			const SDL_Rect*        srcrect,
			const SDL_Rect*        dstrect,
			const double           angle,
			const SDL_Point*       center,
			const SDL_RendererFlip flip)*/
}
