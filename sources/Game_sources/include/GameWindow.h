#pragma once
#include "include/Core.h"
#include "include/Vector2.h"
#include "include/GameObject.h"
#include "include/Fps.h"


class Label;
class Button;

class GameWindow
{
public:
	GameWindow();
	GameWindow(bool fullScreeen);
	GameWindow(const Vector2 &size);
	~GameWindow();
	static GameWindow * instance() { return sm_instance; }

	SDL_Window * GetRawWindow();

	void Initialize();
	void Update();

private:
	SDL_Window											  * m_window;
	SDL_DisplayMode											m_displayMode;
	SDL_Renderer										  * m_renderer;
	Vector2													m_windowSize;
	_FPS													FPS;

	vector<GameObject*>										m_ground;
	SDL_Texture											  * m_bg;
	SDL_Rect												m_bgRect;

	Label												  * m_someText;
	Button												  * m_someBtn;

	template <typename T> void DrawObject(T * object);
	void DrawTexture(SDL_Texture * texture, const SDL_Rect & rect);
	void DrawTexture(SDL_Texture * texture, const SDL_Rect & rect, double angle, 
		const SDL_Point & center, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
	static GameWindow * sm_instance;
};

template<typename T>
inline void GameWindow::DrawObject(T * object)
{
	if (object->IsVisible())
	{
		DrawTexture(object->GetTexture(), object->GetRenderRect());
	}
}
