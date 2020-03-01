#pragma once
#include "include/Core.h"
#include "include/Vector2.h"
#include "include/GameObject.h"
#include "include/Fps.h"

class SettingsWidget;

class EditorWindow
{
public:
	EditorWindow();
	EditorWindow(bool fullScreeen);
	EditorWindow(const Vector2 &size);
	~EditorWindow();
	static EditorWindow * instance() { return sm_instance; }

	SDL_Window * GetRawWindow() { return m_window; }
	SDL_Renderer * GetRenderer() { return m_renderer; }
	const Vector2 & GetWindowSize() { return m_windowSize; }

	void Initialize();
	void Update();

	void DrawObject(GameObject * object);

private:
	SDL_Window											  * m_window;
	SDL_DisplayMode											m_displayMode;
	SDL_Renderer										  * m_renderer;
	Vector2													m_windowSize;
	_FPS													FPS;

	vector<GameObject*>										m_ground;
	SDL_Texture											  * m_bg;
	SDL_Rect												m_bgRect;

	SettingsWidget										  * m_settings;

	void DrawTexture(SDL_Texture * texture, const SDL_Rect & rect);
	void DrawTexture(SDL_Texture * texture, const SDL_Rect & rect, double angle,
		const SDL_Point & center, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
	static EditorWindow * sm_instance;
};